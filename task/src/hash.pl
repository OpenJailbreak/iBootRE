#!/usr/bin/perl

%dict = {};
while(<>) {
    ($addr, $bytes) = split(/:\s*/);
    if($dict{$addr} eq "") {
        $dict{$addr} = $bytes;
    }
}

$start = "0x4ff2e000";
$stop = "0x4fff7ff0";
$hexstart = hex($start);
$hexstop = hex($stop);
$current = $hexstart;
while($current < $hexstop) {
    $address = sprintf("0x%08x", $current);
    if($dict{$address} ne "") {
        print "$address: $dict{$address}";
    }
    $current += 16;
}

