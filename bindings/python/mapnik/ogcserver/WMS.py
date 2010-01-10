#
# This file is part of Mapnik (c++ mapping toolkit)
#
# Copyright (C) 2006 Jean-Francois Doyon
#
# Mapnik is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# $Id: WMS.py 1032 2009-03-30 04:24:01Z dane $

"""Interface for registering map styles and layers for availability in WMS Requests."""

from common import Version, copy_style, copy_layer
from exceptions import OGCException, ServerConfigurationError
from wms111 import ServiceHandler as ServiceHandler111
from wms130 import ServiceHandler as ServiceHandler130
from mapnik import Style, Map, load_map 
import re
import sys

def ServiceHandlerFactory(conf, mapfactory, onlineresource, version):

    if not version:
        version = Version('1.3.0')
    else:
        version = Version(version)
    if version >= '1.3.0':
        return ServiceHandler130(conf, mapfactory, onlineresource)
    else:
        return ServiceHandler111(conf, mapfactory, onlineresource)

class BaseWMSFactory:
    def __init__(self):
        self.layers = {}
        self.ordered_layers = []
        self.styles = {}
        self.aggregatestyles = {}

    def loadXML(self, xmlfile, strict=False):
        tmp_map = Map(0,0)
        load_map (tmp_map, xmlfile, strict)
        for lyr in tmp_map.layers:   
            style_count = len(lyr.styles)
            if style_count == 0:
                raise ServerConfigurationError("Cannot register Layer '%s' without a style" % lyr.name)
            elif style_count == 1:
                style_obj = tmp_map.find_style(lyr.styles[0])
                style_obj = copy_style(style_obj)
                style_name = lyr.styles[0]
                if style_name not in self.aggregatestyles.keys() and style_name not in self.styles.keys():
                    self.register_style(style_name, style_obj)
                self.register_layer(copy_layer(lyr), style_name, extrastyles=(style_name,))
            elif style_count > 1:
                for style_name in lyr.styles:
                    style_obj = tmp_map.find_style(style_name)
                    style_obj = copy_style(style_obj)
                    if style_name not in self.aggregatestyles.keys() and style_name not in self.styles.keys():
                        self.register_style(style_name, style_obj)
                aggregates = tuple([sty for sty in lyr.styles])
                aggregates_name = '%s_aggregates' % lyr.name
                self.register_aggregate_style(aggregates_name,aggregates)
                self.register_layer(copy_layer(lyr), aggregates_name, extrastyles=aggregates)

    def register_layer(self, layer, defaultstyle, extrastyles=()):
        layername = layer.name
        if not layername:
            raise ServerConfigurationError('Attempted to register an unnamed layer.')
        if not re.match('^\+init=epsg:\d+$', layer.srs) and not re.match('^\+proj=.*$', layer.srs):
            raise ServerConfigurationError('Attempted to register a layer without an epsg projection defined.')
        if defaultstyle not in self.styles.keys() + self.aggregatestyles.keys():
            raise ServerConfigurationError('Attempted to register a layer with an non-existent default style.')
        layer.wmsdefaultstyle = defaultstyle
        if isinstance(extrastyles, tuple):
            for stylename in extrastyles:
                if type(stylename) == type(''):
                    if stylename not in self.styles.keys() + self.aggregatestyles.keys():
                        raise ServerConfigurationError('Attempted to register a layer with an non-existent extra style.')
                else:
                    ServerConfigurationError('Attempted to register a layer with an invalid extra style name.')
            layer.wmsextrastyles = extrastyles
        else:
            raise ServerConfigurationError('Layer "%s" was passed an invalid list of extra styles.  List must be a tuple of strings.' % layername)
        self.ordered_layers.append(layer)    
        self.layers[layername] = layer

    def register_style(self, name, style):
        if not name:
            raise ServerConfigurationError('Attempted to register a style without providing a name.')
        if name in self.aggregatestyles.keys() or name in self.styles.keys():
            raise ServerConfigurationError("Attempted to register a style with a name already in use: '%s'" % name)
        if not isinstance(style, Style):
            raise ServerConfigurationError('Bad style object passed to register_style() for style "%s".' % name)
        self.styles[name] = style

    def register_aggregate_style(self, name, stylenames):
        if not name:
            raise ServerConfigurationError('Attempted to register an aggregate style without providing a name.')
        if name in self.aggregatestyles.keys() or name in self.styles.keys():
            raise ServerConfigurationError('Attempted to register an aggregate style with a name already in use.')
        self.aggregatestyles[name] = []
        for stylename in stylenames:
            if stylename not in self.styles.keys():
                raise ServerConfigurationError('Attempted to register an aggregate style containing a style that does not exist.')
            self.aggregatestyles[name].append(stylename)

    def finalize(self):
        if len(self.layers) == 0:
            raise ServerConfigurationError('No layers defined!')
        if len(self.styles) == 0:
            raise ServerConfigurationError('No styles defined!')
        for layer in self.layers.values():
            for style in list(layer.styles) + list(layer.wmsextrastyles):
                if style not in self.styles.keys() + self.aggregatestyles.keys():
                    raise ServerConfigurationError('Layer "%s" refers to undefined style "%s".' % (layer.name, style))