enum {
    kCINoError = 0,
    kCIError   = -1,
    kCICatch   = -2
};

struct CIArgs {
  char *service;
  long nArgs;
  long nReturns;
  
  union {
    struct {			// nArgs=1 + args, nReturns=1 + rets
      const char *forth;
      long     cells[13];
    } interpret;
    
    struct {			// nArgs=2 + args, nReturns=1 + rets
      const char *method;
      long     iHandle;
      long     cells[13];
    } callMethod;
    
    struct {			// nArgs=1, nReturns=1	( device-specifier -- ihandle )
      char *devSpec;	        // IN parameter
      long ihandle;		// RETURN value
    } open;
    
    struct {			// nArgs=1, nReturns=0	( ihandle -- )
      long ihandle;		// IN parameter
    } close;
    
    struct {                    // nArgs=3, nReturns=1 ( ihandle addr length -- actual )
      long ihandle;
      long addr;
      long length;
      long actual;
    } read;
    
    struct {                    // nArgs=3, nReturns=1 ( ihandle addr length -- actual )
      long ihandle;
      long addr;
      long length;
      long actual;
    } write;
    
    struct {                    // nArgs=3, nReturns=1 ( ihandle pos.high pos.low -- result )
      long ihandle;
      long pos_high;
      long pos_low;
      long result;
    } seek;
    
    struct {			// nArgs=3, nReturns=1
      long virt;
      long size;
      long align;
      long baseaddr;
    } claim;
    
    struct {			// nArgs=2, nReturns=0
      long virt;
      long size;
    } release;
    
    struct {			// nArgs=1, nReturns=1	( phandle -- peer-phandle )
      long phandle;	        // IN parameter
      long peerPhandle;	// RETURN value
    } peer;
    
    struct {			// nArgs=1, nReturns=1	( phandle -- child-phandle )
      long phandle;		// IN parameter
      long childPhandle;	// RETURN value
    } child;
    
    struct {			// nArgs=1, nReturns=1	( phandle -- parent-phandle )
      long childPhandle;	// IN parameter
      long parentPhandle;	// RETURN value
    } parent;
    
    struct {			// nArgs=1, nReturns=1	( devSpec -- phandle )
      char *devSpec;	        // IN parameter
      long phandle;	        // RETURN value
    } finddevice;
    
    struct {                    // nArgs=3, nReturns=1 ( ihandle buf buflen -- length )
      long ihandle;           // IN ihandle
      char   *buf;              // IN buf
      long buflen;            // IN buflen
      long length;            // RETURN length
    } instanceToPath;
    
    struct {                    // nArgs=1, nReturns=1 ( ihandle -- phandle )
      long ihandle;           // IN ihandle
      long phandle;           // RETURN phandle
    } instanceToPackage;
    
    struct {                    // nArgs=3, nReturns=1 ( phandle buf buflen -- length )
      long phandle;           // IN phandle
      char   *buf;              // IN buf
      long buflen;            // IN buflen
      long length;            // RETURN length
    } packageToPath;
    
    struct {			// nArgs=2, nReturns=1	( phandle name -- size )
      long phandle;		// IN parameter
      char   *name;		// IN parameter
      long size;		// RETURN value
    } getproplen;
    
    struct {			// nArgs=4, nReturns=1	( phandle name buf buflen -- size )
      long phandle;		// IN parameter
      char   *name;		// IN parameter
      char   *buf;		// IN parameter
      long buflen;		// IN parameter
      long size;		// RETURN value
    } getprop;
    
    struct {			// nArgs=3, nReturns=1	( phandle previous buf -- flag )
      long phandle;		// IN parameter
      char *previous;		// IN parameter
      char *buf;		// IN parameter
      long flag;		// RETURN value
    } nextprop;
    
    struct {			// nArgs=4, nReturns=1	( phandle name buf buflen -- size )
      long phandle;		// IN parameter
      char *name;		// IN parameter
      char *buf;		// IN parameter
      long buflen;		// IN parameter
      long size;		// RETURN value
    } setprop;
    
    struct {			// nArgs=1, nReturns=0
      char *bootspec;
    } boot;
  } args;
};
