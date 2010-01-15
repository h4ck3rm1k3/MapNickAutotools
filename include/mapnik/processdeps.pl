use strict;
use warnings;
# process the dependancies
# 1. read in the deps.
# 2. determine the proper order
# 3. make the gcp

sub proc_deps
{
    my $f=shift;
    open IN,"$f";
    my @deps;
    my $first;
    while (<IN>)
    {
	s/\\$/ /g; # strip off the slash at the end
	my @parts = split " ",$_;

	# head of rule
	if (/(\w+\.o)\s*:\s*/)
	{

	    $first=$1;
	    $first =~ s/\.o/.hpp.gch/;
#	    warn "FOUND: $first";
	}
	else
	{
	    # tail of rule
#	    warn $_;
	}


	push @deps, grep {	   
	    #next if /^\//;
#	    warn $_;
	    s/^\.\.\/mapnik\///;
		#$_
	} @parts;


    }

    die "cannot procss file $f " unless $first;
    print  $first . ":" . join (" ", @deps) . "\n";
    
    close IN;
}

my $file =shift;
if ($file)
{
	proc_deps $file;
}
else
{
    opendir(my $dh, ".") || die "can't opendir .: $!";
    map {
	proc_deps $_;
    }  
    grep { /\.d$/ && -f "$_" } readdir($dh);
    closedir $dh;
}


