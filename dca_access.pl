#!/usr/bin/perl

use File::stat;
use strict;

my $filename  = $ARGV[0];

my $fb = stat($filename);

if (defined $fb) {
	print scalar localtime($fb->mtime);
} else {
	print "Never Accessed";
}
