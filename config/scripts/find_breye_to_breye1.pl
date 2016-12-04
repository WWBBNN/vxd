#!/bin/sh
# -*- perl -*-
exec perl -w -x $0 ${1+"$@"}
#!perl
#line 6
# If Windows barfs at line 3 here, you will need to run perl -x this_file.pl
# You can set up as a permanent file association using the following commands
#  >assoc .pl-PerlScript
#  >ftype PerlScript=Perl=C:\Perl\bin\Perl.exe -x "%1" %*


# usage: convertvil2tovil.run_me_second.pl file_or_directory_name
# Modifies files so as to deal with vil2 to vil renaming.
# Only run this script after running convertviltovil1.run_me_first.pl

use strict;
use File::Find ();
use File::Copy ();

# Set the variable $File::Find::dont_use_nlink if you're using AFS,
# since AFS cheats.


sub convert {
    my ($src, $dest)= @_;
    open(OUTFILE,">$dest") or die "Can't open $src";
    open(INFILE,"<$src") or die "Can't open $dest";

    while (<INFILE>)
    {
# CMake
# Match either a trailing space or parenthesis with leading space
s!\ vidpro\ !\ vidpro1\ !g;
s!\b\ vidpro\ !\ vidpro1\ !g;
s!\b\ vidpro\)!\ vidpro1\)!g;
s!\ dbvidpro\ !\ dbvidpro1\ !g;
s!\b\ dbvidpro\ !\ dbvidpro1\ !g;
s!\b\ dbvidpro\)!\ dbvidpro1\)!g;

s!\b\ bpro\ !\ bpro1\ !g;
s!\ bpro\ !\ bpro1\ !g;
s!\b\ bpro\)!\ bpro1\)!g;
s!\ bvis\ !\ bvis1\ !g;
s!\b\ bvis\ !\ bvis1\ !g;
s!\b\ bvis\)!\ bvis1\)!g;
s!\ dbvis\ !\ dbvis1\ !g;
s!\b\ dbvis\ !\ dbvis1\ !g;
s!\b\ dbvis\)!\ dbvis1\)!g;
s!\ vorl\ !\ vorl1\ !g;
s!\b\ vorl\ !\ vorl1\ !g;
s!\b\ vorl\)!\ vorl1\)!g;

# Match either a trailing space or parenthesis with leading parenthesis
s!\b\(vidpro\ !\(vidpro1\ !g;
s!\b\(vidpro\)!\(vidpro1\)!g;
s!\b\(dbvidpro\ !\(dbvidpro1\ !g;
s!\b\(dbvidpro\)!\(dbvidpro1\)!g;

s!\b\(bpro\ !\(bpro1\ !g;
s!\b\(bpro\)!\(bpro1\)!g;
s!\b\(bvis\ !\(bvis1\ !g;
s!\b\(bvis\)!\(bvis1\)!g;
s!\b\(dbvis\)!\(dbvis1\)!g;
s!\b\(vorl\)!\(vorl1\)!g;

s!vorl\.!vorl1\.!g;
# Includes
s!bvis\/!bvis1\/!g;
s!dbvis\/!dbvis1\/!g;
s!bpro\/!bpro1\/!g;
s!vidpro\/!vidpro1\/!g;
s!dbvidpro\/!dbvidpro1\/!g;
s!vorl\/!vorl1\/!g;
s!breye\/!breye1\/!g;
s!\/breye\ !\/breye1\ !g;
s!\/breye\)!\/breye1\)!g;
# Classes
s!\bvidpro_!vidpro1_!g;
s!\bdbvidpro_!dbvidpro1_!g;
s!\bbpro_!bpro1_!g;
s!\bbvis_!bvis1_!g;
s!\bdbvis_!dbvis1_!g;
s!vorl_!vorl1_!g;

        print OUTFILE;
    }
    close OUTFILE;
    close INFILE;

}


sub mentions_breye {
    my ($filename)= ($_);
#    print "Checking $filename\n";
    open(INFILE,"<$filename") or die "Can't open $filename";

    while (<INFILE>)
    {
        if (/\bbpro/ || /\bbvis/ ||/\bvidpro/ ||/\bdbpro/ ||/\bdbvis/)
        {
          close INFILE;
          return 1;
        }
    }
    close INFILE;
    return 0;
}



sub wanted {
    my ($filename) = $File::Find::name;
    my $backup;
    my $scr;
#    print "Found1 $filename\n";
    if (! -f $filename)  {return;}
#    print "Found $filename\n";
    if ($filename =~ /CVS/) {return;}
    if ($filename =~ /\.old/) {return;}
    if ($filename =~ /\~/) {return;}
    if ($filename =~ /\#/) {return;}
#    print "Found3 $filename\n";
    
    if (mentions_breye($filename))
    {
        print "Breye in $filename\n";
	$backup = "$filename.old";
        rename $filename, $backup or die "Unable to create backup $backup";
        # Copy backup into original file
        convert $backup, $filename;
    }
}


print "Searching $ARGV[0]\n";
# Traverse desired filesystems
File::Find::find({ wanted => \&wanted, follow => 0, no_chdir => 1 } , $ARGV[0]);
exit;
