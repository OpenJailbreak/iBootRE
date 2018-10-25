#!/usr/bin/perl

$prev = 0;
$count = 0;
@file = <>;
$size = $#file;
foreach(@file) {
    $count++;
    $line = $_;
    next if($_ eq "/\r\n/");
    my ($addr, $bytes) = split(/:\s*/);
    if(hex($addr) != $prev + 16 && $prev != 0) {
        $current = $prev+16;
        while($current < hex($addr)) {
            printf("Missing 0x%08x\n", $current);
            $current += 16;
        }
    }
    
    $prev = hex($addr);
}


# find good lines
# log bad lines
