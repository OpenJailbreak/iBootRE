struct CacheEntry {
  CICell    ih;
  long      time;
  long long offset;
};

enum {
    kCacheSize            kFSCacheSize
    kCacheMinBlockSize    0x200
    kCacheMaxBlockSize    0x4000
    kCacheMaxEntries      kCacheSize / 0x200
};
