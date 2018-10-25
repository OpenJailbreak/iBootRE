/* Signatures used to differentiate between HFS and HFS Plus volumes */
enum {
	kHFSSigWord		= 0x4244,	/* 'BD' in ASCII */
	kHFSPlusSigWord		= 0x482B,	/* 'H+' in ASCII */
	kHFSXSigWord		= 0x4858,	/* 'HX' in ASCII */

	kHFSPlusVersion		= 0x0004,	/* 'H+' volumes are version 4 only */
	kHFSXVersion		= 0x0005,	/* 'HX' volumes start with version 5 */

	kHFSPlusMountVersion	= 0x31302E30,	/* '10.0' for Mac OS X */
	kHFSJMountVersion	= 0x4846534a,	/* 'HFSJ' for journaled HFS+ on OS X */
	kFSKMountVersion	= 0x46534b21	/* 'FSK!' for failed journal replay */
};

/*
 * Indirect link files (hard links) have the following type/creator.
 */
enum {
	kHardLinkFileType = 0x686C6E6B,  /* 'hlnk' */
	kHFSPlusCreator   = 0x6866732B   /* 'hfs+' */
};


/*
 *	File type and creator for symbolic links
 */
enum {
      kSymLinkFileType  = 0x736C6E6B, /* 'slnk' */
      kSymLinkCreator   = 0x72686170  /* 'rhap' */
};

/* Unicode strings are used for HFS Plus file and folder names */
struct HFSUniStr255 {
	unsigned short	length;		/* number of unicode characters */
	unsigned short	unicode[255];	/* unicode characters */
};

enum {
	kHFSMaxVolumeNameChars		= 27,
	kHFSMaxFileNameChars		= 31,
	kHFSPlusMaxFileNameChars	= 255
};


/* Extent overflow file data structures */

/* HFS Extent key */
struct HFSExtentKey {
	unsigned char 	keyLength;	/* length of key, excluding this field */
	unsigned char 	forkType;	/* 0 = data fork, FF = resource fork */
	unsigned int 	fileID;		/* file ID */
	unsigned short 	startBlock;	/* first file allocation block number in this extent */
};

/* HFS Plus Extent key */
struct HFSPlusExtentKey {
	unsigned short 	keyLength;		/* length of key, excluding this field */
	unsigned char 	forkType;		/* 0 = data fork, FF = resource fork */
	unsigned char 	pad;			/* make the other fields align on 32-bit boundary */
	unsigned int 	fileID;			/* file ID */
	unsigned int 	startBlock;		/* first file allocation block number in this extent */
};

/* Number of extent descriptors per extent record */
enum {
	kHFSExtentDensity	= 3,
	kHFSPlusExtentDensity	= 8
};

/* HFS extent descriptor */
struct HFSExtentDescriptor {
	unsigned short 	startBlock;		/* first allocation block */
	unsigned short 	blockCount;		/* number of allocation blocks */
};

/* HFS Plus extent descriptor */
struct HFSPlusExtentDescriptor {
	unsigned int 	startBlock;		/* first allocation block */
	unsigned int 	blockCount;		/* number of allocation blocks */
};

/* Finder information */
struct FndrFileInfo {
	unsigned int 	fdType;		/* file type */
	unsigned int 	fdCreator;	/* file creator */
	unsigned short 	fdFlags;	/* Finder flags */
	struct {
	    signed short	v;		/* file's location */
	    signed short	h;
	} fdLocation;
	signed short 	opaque;
};

struct FndrDirInfo {
	struct {			/* folder's window rectangle */
	    signed short	top;
	    signed short	left;
	    signed short	bottom;
	    signed short	right;
	} frRect;
	unsigned short 	frFlags;	/* Finder flags */
	struct {
	    unsigned short	v;		/* folder's location */
	    unsigned short	h;
	} frLocation;
	signed short 	opaque;
};

struct FndrOpaqueInfo {
	signed char opaque[16];
};


/* HFS Plus Fork data info - 80 bytes */
struct HFSPlusForkData {
	unsigned long long 		logicalSize;	/* fork's logical size in bytes */
	unsigned int 		clumpSize;	/* fork's clump size in bytes */
	unsigned int 		totalBlocks;	/* total blocks used by this fork */
	struct HFSPlusExtentDescriptor 	extents[8];	/* initial set of extents */
};


/* Mac OS X has 16 bytes worth of "BSD" info.
 *
 * Note:  Mac OS 9 implementations and applications
 * should preserve, but not change, this information.
 */
struct HFSPlusBSDInfo {
	unsigned int 	ownerID;	/* user-id of owner or hard link chain previous link */
	unsigned int 	groupID;	/* group-id of owner or hard link chain next link */
	unsigned char 	adminFlags;	/* super-user changeable flags */
	unsigned char 	ownerFlags;	/* owner changeable flags */
	unsigned short 	fileMode;	/* file type and permission bits */
	union {
	    unsigned int	iNodeNum;	/* indirect node number (hard links only) */
	    unsigned int	linkCount;	/* links that refer to this indirect node */
	    unsigned int	rawDevice;	/* special file device (FBLK and FCHR only) */
	} special;
};

/* Catalog file data structures */

enum {
	kHFSRootParentID		= 1,	/* Parent ID of the root folder */
	kHFSRootFolderID		= 2,	/* Folder ID of the root folder */
	kHFSExtentsFileID		= 3,	/* File ID of the extents file */
	kHFSCatalogFileID		= 4,	/* File ID of the catalog file */
	kHFSBadBlockFileID		= 5,	/* File ID of the bad allocation block file */
	kHFSAllocationFileID		= 6,	/* File ID of the allocation file (HFS Plus only) */
	kHFSStartupFileID		= 7,	/* File ID of the startup file (HFS Plus only) */
	kHFSAttributesFileID		= 8,	/* File ID of the attribute file (HFS Plus only) */
	kHFSAttributeDataFileID         = 13,	/* Used in Mac OS X runtime for extent based attributes */
	                                        /* kHFSAttributeDataFileID is never stored on disk. */
	kHFSRepairCatalogFileID		= 14,	/* Used when rebuilding Catalog B-tree */
	kHFSBogusExtentFileID		= 15,	/* Used for exchanging extents in extents file */
	kHFSFirstUserCatalogNodeID	= 16
};

/* HFS catalog key */
struct HFSCatalogKey {
	unsigned char 	keyLength;		/* key length (in bytes) */
	unsigned char 	reserved;		/* reserved (set to zero) */
	unsigned int 	parentID;		/* parent folder ID */
	unsigned char 	nodeName[kHFSMaxFileNameChars + 1]; /* catalog node name */
};

/* HFS Plus catalog key */
struct HFSPlusCatalogKey {
	unsigned short 		keyLength;	/* key length (in bytes) */
	unsigned int 		parentID;	/* parent folder ID */
	struct HFSUniStr255 		nodeName;	/* catalog node name */
};

/* Catalog record types */
enum {
	/* HFS Catalog Records */
	kHFSFolderRecord		= 0x0100,	/* Folder record */
	kHFSFileRecord			= 0x0200,	/* File record */
	kHFSFolderThreadRecord		= 0x0300,	/* Folder thread record */
	kHFSFileThreadRecord		= 0x0400,	/* File thread record */

	/* HFS Plus Catalog Records */
	kHFSPlusFolderRecord		= 1,		/* Folder record */
	kHFSPlusFileRecord		= 2,		/* File record */
	kHFSPlusFolderThreadRecord	= 3,		/* Folder thread record */
	kHFSPlusFileThreadRecord	= 4		/* File thread record */
};


/* Catalog file record flags */
enum {
	kHFSFileLockedBit	= 0x0000,	/* file is locked and cannot be written to */
	kHFSFileLockedMask	= 0x0001,

	kHFSThreadExistsBit	= 0x0001,	/* a file thread record exists for this file */
	kHFSThreadExistsMask	= 0x0002,

	kHFSHasAttributesBit	= 0x0002,	/* object has extended attributes */
	kHFSHasAttributesMask	= 0x0004,

	kHFSHasSecurityBit	= 0x0003,	/* object has security data (ACLs) */
	kHFSHasSecurityMask	= 0x0008,

	kHFSHasFolderCountBit	= 0x0004,	/* only for HFSX, folder maintains a separate sub-folder count */
	kHFSHasFolderCountMask	= 0x0010,	/* (sum of folder records and directory hard links) */

	kHFSHasLinkChainBit	= 0x0005,	/* has hardlink chain (inode or link) */
	kHFSHasLinkChainMask	= 0x0020,

	kHFSHasChildLinkBit	= 0x0006,	/* folder has a child that's a dir link */
	kHFSHasChildLinkMask	= 0x0040
};


/* HFS catalog folder record - 70 bytes */
struct HFSCatalogFolder {
	signed short 		recordType;		/* == kHFSFolderRecord */
	unsigned short 		flags;			/* folder flags */
	unsigned short 		valence;		/* folder valence */
	unsigned int		folderID;		/* folder ID */
	unsigned int 		createDate;		/* date and time of creation */
	unsigned int 		modifyDate;		/* date and time of last modification */
	unsigned int 		backupDate;		/* date and time of last backup */
	struct FndrDirInfo 		userInfo;		/* Finder information */
	struct FndrOpaqueInfo		finderInfo;		/* additional Finder information */
	unsigned int 		reserved[4];		/* reserved - initialized as zero */
};

/* HFS Plus catalog folder record - 88 bytes */
struct HFSPlusCatalogFolder {
	signed short 		recordType;		/* == kHFSPlusFolderRecord */
	unsigned short 		flags;			/* file flags */
	unsigned int 		valence;		/* folder's item count */
	unsigned int 		folderID;		/* folder ID */
	unsigned int 		createDate;		/* date and time of creation */
	unsigned int 		contentModDate;		/* date and time of last content modification */
	unsigned int 		attributeModDate;	/* date and time of last attribute modification */
	unsigned int 		accessDate;		/* date and time of last access (MacOS X only) */
	unsigned int 		backupDate;		/* date and time of last backup */
	struct HFSPlusBSDInfo		bsdInfo;		/* permissions (for MacOS X) */
	struct FndrDirInfo 		userInfo;		/* Finder information */
	struct FndrOpaqueInfo	 	finderInfo;		/* additional Finder information */
	unsigned int 		textEncoding;		/* hint for name conversions */
	unsigned int 		folderCount;		/* number of enclosed folders, active when HasFolderCount is set */
};

/* HFS catalog file record - 102 bytes */
struct HFSCatalogFile {
	signed short 		recordType;		/* == kHFSFileRecord */
	unsigned char 		flags;			/* file flags */
	signed char 			fileType;		/* file type (unused ?) */
	struct FndrFileInfo 		userInfo;		/* Finder information */
	unsigned int 		fileID;			/* file ID */
	unsigned short 		dataStartBlock;		/* not used - set to zero */
	signed int 		dataLogicalSize;	/* logical EOF of data fork */
	signed int 		dataPhysicalSize;	/* physical EOF of data fork */
	unsigned short		rsrcStartBlock;		/* not used - set to zero */
	signed int			rsrcLogicalSize;	/* logical EOF of resource fork */
	signed int			rsrcPhysicalSize;	/* physical EOF of resource fork */
	unsigned int		createDate;		/* date and time of creation */
	unsigned int		modifyDate;		/* date and time of last modification */
	unsigned int		backupDate;		/* date and time of last backup */
	struct FndrOpaqueInfo		finderInfo;		/* additional Finder information */
	unsigned short		clumpSize;		/* file clump size (not used) */
	struct HFSExtentDescriptor		dataExtents[3];		/* first data fork extent record */
	struct HFSExtentDescriptor		rsrcExtents[3];		/* first resource fork extent record */
	unsigned int		reserved;		/* reserved - initialized as zero */
};

/* HFS Plus catalog file record - 248 bytes */
struct HFSPlusCatalogFile {
	signed short 		recordType;		/* == kHFSPlusFileRecord */
	unsigned short 		flags;			/* file flags */
	unsigned int 		reserved1;		/* reserved - initialized as zero */
	unsigned int 		fileID;			/* file ID */
	unsigned int 		createDate;		/* date and time of creation */
	unsigned int 		contentModDate;		/* date and time of last content modification */
	unsigned int 		attributeModDate;	/* date and time of last attribute modification */
	unsigned int 		accessDate;		/* date and time of last access (MacOS X only) */
	unsigned int 		backupDate;		/* date and time of last backup */
	struct HFSPlusBSDInfo 		bsdInfo;		/* permissions (for MacOS X) */
	struct FndrFileInfo 		userInfo;		/* Finder information */
	struct FndrOpaqueInfo	 	finderInfo;		/* additional Finder information */
	unsigned int 		textEncoding;		/* hint for name conversions */
	unsigned int 		reserved2;		/* reserved - initialized as zero */

	/* Note: these start on double long (64 bit) boundary */
	struct HFSPlusForkData 	dataFork;		/* size and block data for data fork */
	struct HFSPlusForkData 	resourceFork;		/* size and block data for resource fork */
};

/* HFS catalog thread record - 46 bytes */
struct HFSCatalogThread {
	signed short 	recordType;		/* == kHFSFolderThreadRecord or kHFSFileThreadRecord */
	signed int 	reserved[2];		/* reserved - initialized as zero */
	unsigned int 	parentID;		/* parent ID for this catalog node */
	unsigned char 	nodeName[kHFSMaxFileNameChars + 1]; /* name of this catalog node */
};

/* HFS Plus catalog thread record -- 264 bytes */
struct HFSPlusCatalogThread {
	signed short 	recordType;		/* == kHFSPlusFolderThreadRecord or kHFSPlusFileThreadRecord */
	signed short 	reserved;		/* reserved - initialized as zero */
	unsigned int 	parentID;		/* parent ID for this catalog node */
	struct HFSUniStr255 	nodeName;		/* name of this catalog node (variable length) */
};

/*
  	These are the types of records in the attribute B-tree.  The values were
  	chosen so that they wouldn't conflict with the catalog record types.
*/
enum {
	kHFSPlusAttrInlineData	= 0x10,   /* attributes whose data fits in a b-tree node */
	kHFSPlusAttrForkData	= 0x20,   /* extent based attributes (data lives in extents) */
	kHFSPlusAttrExtents	= 0x30    /* overflow extents for large attributes */
};


/*
  	HFSPlusAttrForkData
  	For larger attributes, whose value is stored in allocation blocks.
  	If the attribute has more than 8 extents, there will be additional
  	records (of type HFSPlusAttrExtents) for this attribute.
*/
struct HFSPlusAttrForkData {
	unsigned int 	recordType;		/* == kHFSPlusAttrForkData*/
	unsigned int 	reserved;
	struct HFSPlusForkData theFork;		/* size and first extents of value*/
};

/*
  	HFSPlusAttrExtents
  	This record contains information about overflow extents for large,
  	fragmented attributes.
*/
struct HFSPlusAttrExtents {
	unsigned int 		recordType;	/* == kHFSPlusAttrExtents*/
	unsigned int 		reserved;
	struct HFSPlusExtentDescriptor	extents[8];	/* additional extents*/
};

/*
 * Atrributes B-tree Data Record
 *
 * For small attributes, whose entire value is stored
 * within a single B-tree record.
 */
struct HFSPlusAttrData {
	unsigned int    recordType;   /* == kHFSPlusAttrInlineData */
	unsigned int    reserved[2];
	unsigned int    attrSize;     /* size of attribute data in bytes */
	unsigned char     attrData[2];  /* variable length */
};


/* HFSPlusAttrInlineData is obsolete use HFSPlusAttrData instead */
struct HFSPlusAttrInlineData {
	unsigned int 	recordType;
	unsigned int 	reserved;
	unsigned int 	logicalSize;
	unsigned char 	userData[2];
};


/*	A generic Attribute Record*/
union HFSPlusAttrRecord {
	unsigned int 		recordType;
	struct HFSPlusAttrInlineData 	inlineData;   /* NOT USED */
	struct HFSPlusAttrData 	attrData;
	struct HFSPlusAttrForkData 	forkData;
	struct HFSPlusAttrExtents 	overflowExtents;
};

/* Attribute key */
enum { kHFSMaxAttrNameLen = 127 };
struct HFSPlusAttrKey {
	unsigned short     keyLength;       /* key length (in bytes) */
	unsigned short     pad;	       /* set to zero */
	unsigned int     fileID;          /* file associated with attribute */
	unsigned int     startBlock;      /* first allocation block number for extents */
	unsigned short     attrNameLen;     /* number of unicode characters */
	unsigned short     attrName[kHFSMaxAttrNameLen];   /* attribute name (Unicode) */
};


/* Key and node lengths */
enum {
	kHFSPlusCatalogMinNodeSize	= 4096,
	kHFSPlusExtentMinNodeSize	= 512,
	kHFSPlusAttrMinNodeSize		= 4096
};

/* HFS and HFS Plus volume attribute bits */
enum {
	/* Bits 0-6 are reserved (always cleared by MountVol call) */
	kHFSVolumeHardwareLockBit	= 7,		/* volume is locked by hardware */
	kHFSVolumeUnmountedBit		= 8,		/* volume was successfully unmounted */
	kHFSVolumeSparedBlocksBit	= 9,		/* volume has bad blocks spared */
	kHFSVolumeNoCacheRequiredBit = 10,		/* don't cache volume blocks (i.e. RAM or ROM disk) */
	kHFSBootVolumeInconsistentBit = 11,		/* boot volume is inconsistent (System 7.6 and later) */
	kHFSCatalogNodeIDsReusedBit = 12,
	kHFSVolumeJournaledBit = 13,			/* this volume has a journal on it */
	kHFSVolumeInconsistentBit = 14,			/* serious inconsistencies detected at runtime */
	kHFSVolumeSoftwareLockBit	= 15,		/* volume is locked by software */
	/*
	 * HFS only has 16 bits of attributes in the MDB, but HFS Plus has 32 bits.
	 * Therefore, bits 16-31 can only be used on HFS Plus.
	 */
	kHFSUnusedNodeFixBit = 31,				/* Unused nodes in the Catalog B-tree have been zero-filled.  See Radar #6947811. */
	
	kHFSVolumeHardwareLockMask	= 1 << kHFSVolumeHardwareLockBit,
	kHFSVolumeUnmountedMask		= 1 << kHFSVolumeUnmountedBit,
	kHFSVolumeSparedBlocksMask	= 1 << kHFSVolumeSparedBlocksBit,
	kHFSVolumeNoCacheRequiredMask = 1 << kHFSVolumeNoCacheRequiredBit,
	kHFSBootVolumeInconsistentMask = 1 << kHFSBootVolumeInconsistentBit,
	kHFSCatalogNodeIDsReusedMask = 1 << kHFSCatalogNodeIDsReusedBit,
	kHFSVolumeJournaledMask	= 1 << kHFSVolumeJournaledBit,
	kHFSVolumeInconsistentMask = 1 << kHFSVolumeInconsistentBit,
	kHFSVolumeSoftwareLockMask	= 1 << kHFSVolumeSoftwareLockBit,
	kHFSUnusedNodeFixMask = 1 << kHFSUnusedNodeFixBit,
	kHFSMDBAttributesMask		= 0x8380
};

enum {
	kHFSUnusedNodesFixDate = 0xc5ef2480		/* March 25, 2009 */
};

/* HFS Master Directory Block - 162 bytes */
/* Stored at sector #2 (3rd sector) and second-to-last sector. */
struct HFSMasterDirectoryBlock {
	unsigned short 		drSigWord;	/* == kHFSSigWord */
	unsigned int 		drCrDate;	/* date and time of volume creation */
	unsigned int 		drLsMod;	/* date and time of last modification */
	unsigned short 		drAtrb;		/* volume attributes */
	unsigned short 		drNmFls;	/* number of files in root folder */
	unsigned short 		drVBMSt;	/* first block of volume bitmap */
	unsigned short 		drAllocPtr;	/* start of next allocation search */
	unsigned short 		drNmAlBlks;	/* number of allocation blocks in volume */
	unsigned int 		drAlBlkSiz;	/* size (in bytes) of allocation blocks */
	unsigned int 		drClpSiz;	/* default clump size */
	unsigned short 		drAlBlSt;	/* first allocation block in volume */
	unsigned int 		drNxtCNID;	/* next unused catalog node ID */
	unsigned short 		drFreeBks;	/* number of unused allocation blocks */
	unsigned char 		drVN[kHFSMaxVolumeNameChars + 1];  /* volume name */
	unsigned int 		drVolBkUp;	/* date and time of last backup */
	unsigned short 		drVSeqNum;	/* volume backup sequence number */
	unsigned int 		drWrCnt;	/* volume write count */
	unsigned int 		drXTClpSiz;	/* clump size for extents overflow file */
	unsigned int 		drCTClpSiz;	/* clump size for catalog file */
	unsigned short 		drNmRtDirs;	/* number of directories in root folder */
	unsigned int 		drFilCnt;	/* number of files in volume */
	unsigned int 		drDirCnt;	/* number of directories in volume */
	unsigned int 		drFndrInfo[8];	/* information used by the Finder */
	unsigned short 		drEmbedSigWord;	/* embedded volume signature (formerly drVCSize) */
	struct HFSExtentDescriptor	drEmbedExtent;	/* embedded volume location and size (formerly drVBMCSize and drCtlCSize) */
	unsigned int		drXTFlSize;	/* size of extents overflow file */
	struct HFSExtentDescriptor		drXTExtRec[3];	/* extent record for extents overflow file */
	unsigned int 		drCTFlSize;	/* size of catalog file */
	struct HFSExtentDescriptor 	drCTExtRec[3];	/* extent record for catalog file */
};


/* HFS Plus Volume Header - 512 bytes */
/* Stored at sector #2 (3rd sector) and second-to-last sector. */
struct HFSPlusVolumeHeader {
	unsigned short 	signature;		/* == kHFSPlusSigWord */
	unsigned short 	version;		/* == kHFSPlusVersion */
	unsigned int 	attributes;		/* volume attributes */
	unsigned int 	lastMountedVersion;	/* implementation version which last mounted volume */
	unsigned int 	journalInfoBlock;	/* block addr of journal info (if volume is journaled, zero otherwise) */

	unsigned int 	createDate;		/* date and time of volume creation */
	unsigned int 	modifyDate;		/* date and time of last modification */
	unsigned int 	backupDate;		/* date and time of last backup */
	unsigned int 	checkedDate;		/* date and time of last disk check */

	unsigned int 	fileCount;		/* number of files in volume */
	unsigned int 	folderCount;		/* number of directories in volume */

	unsigned int 	blockSize;		/* size (in bytes) of allocation blocks */
	unsigned int 	totalBlocks;		/* number of allocation blocks in volume (includes this header and VBM*/
	unsigned int 	freeBlocks;		/* number of unused allocation blocks */

	unsigned int 	nextAllocation;		/* start of next allocation search */
	unsigned int 	rsrcClumpSize;		/* default resource fork clump size */
	unsigned int 	dataClumpSize;		/* default data fork clump size */
	unsigned int 	nextCatalogID;		/* next unused catalog node ID */

	unsigned int 	writeCount;		/* volume write count */
	unsigned long long 	encodingsBitmap;	/* which encodings have been use  on this volume */

	unsigned char 	finderInfo[32];		/* information used by the Finder */

	struct HFSPlusForkData	 allocationFile;	/* allocation bitmap file */
	struct HFSPlusForkData  extentsFile;		/* extents B-tree file */
	struct HFSPlusForkData  catalogFile;		/* catalog B-tree file */
	struct HFSPlusForkData  attributesFile;	/* extended attributes B-tree file */
	struct HFSPlusForkData	 startupFile;		/* boot file (secondary loader) */
};


/* B-tree structures */

enum BTreeKeyLimits{
	kMaxKeyLength	= 520
};

union BTreeKey{
	unsigned char	length8;
	unsigned short	length16;
	unsigned char	rawData [kMaxKeyLength+2];
};

/* BTNodeDescriptor -- Every B-tree node starts with these fields. */
struct BTNodeDescriptor {
	unsigned int	fLink;			/* next node at this level*/
	unsigned int 	bLink;			/* previous node at this level*/
	signed char 		kind;			/* kind of node (leaf, index, header, map)*/
	unsigned char 	height;			/* zero for header, map; child is one more than parent*/
	unsigned short 	numRecords;		/* number of records in this node*/
	unsigned short 	reserved;		/* reserved - initialized as zero */
};

/* Constants for BTNodeDescriptor kind */
enum {
	kBTLeafNode	= -1,
	kBTIndexNode	= 0,
	kBTHeaderNode	= 1,
	kBTMapNode	= 2
};

/* BTHeaderRec -- The first record of a B-tree header node */
struct BTHeaderRec {
	unsigned short	treeDepth;		/* maximum height (usually leaf nodes) */
	unsigned int 	rootNode;		/* node number of root node */
	unsigned int 	leafRecords;		/* number of leaf records in all leaf nodes */
	unsigned int 	firstLeafNode;		/* node number of first leaf node */
	unsigned int 	lastLeafNode;		/* node number of last leaf node */
	unsigned short 	nodeSize;		/* size of a node, in bytes */
	unsigned short 	maxKeyLength;		/* reserved */
	unsigned int 	totalNodes;		/* total number of nodes in tree */
	unsigned int 	freeNodes;		/* number of unused (free) nodes in tree */
	unsigned short 	reserved1;		/* unused */
	unsigned int 	clumpSize;		/* reserved */
	unsigned char 	btreeType;		/* reserved */
	unsigned char 	keyCompareType;		/* Key string Comparison Type */
	unsigned int 	attributes;		/* persistent attributes about the tree */
	unsigned int 	reserved3[16];		/* reserved */
};

/* Constants for BTHeaderRec attributes */
enum {
	kBTBadCloseMask		 = 0x00000001,	/* reserved */
	kBTBigKeysMask		 = 0x00000002,	/* key length field is 16 bits */
	kBTVariableIndexKeysMask = 0x00000004	/* keys in index nodes are variable length */
};


/* Catalog Key Name Comparison Type */
enum {
	kHFSCaseFolding   = 0xCF,  /* case folding (case-insensitive) */
	kHFSBinaryCompare = 0xBC  /* binary compare (case-sensitive) */
};

