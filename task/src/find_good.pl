#!/usr/bin/perl

foreach(<>) {
    $error = 0;
    next if($_ eq "\r\n/");
    my ($addr, $bytes) = split(/:\s*/);
    if($addr !~ /^.{10}$/) {
        if($addr ne "\r\n") {
            #print("Invalid Address: $addr\n");
            next;
        }
        $error = 1;
    }
    
    my $count = 0;
    foreach( split(/\s/, $bytes) ) {
        $count++;
        if($count > 16) {
            #print("Too Many Bytes: $addr\n");
            $error = 1;
            last;
       }
       
       if($_ !~ /^.{2}$/) {
            #print("Missing Nyble: $addr\n");
            $error = 1;
            next;
        }
    }
    
    if($error == 0 && $count == 16) {
        print "$addr: $bytes";
    }
}

