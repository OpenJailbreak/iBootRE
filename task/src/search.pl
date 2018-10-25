#!/usr/bin/perl

$found = 0;
open($FD, "good.txt");
foreach(<$FD>) {
    next if($_ eq "\r\n/");
    my ($addr, $bytes) = split(/:\s*/);
    if($addr eq $ARGV[0]) {
        print "$addr: $bytes";
        $found = 1;
        last;
    }
}
close($FD);
