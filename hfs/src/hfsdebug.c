/*
 *
 *  greenpois0n - payload/src/hfsplus.c
 *  (c) 2010 Chronic-Dev Team
 *
 */

#include "common.h"
#include "hfsplus.h"

void printVolumeHeader(HFSPlusVolumeHeader* header) {
	printf("signature = 0x%x\n", header->signature);
	printf("version = 0x%x\n", header->version);
	printf("attributes = 0x%x\n", header->attributes);
	printf("lastMountedVersion = 0x%x\n", header->lastMountedVersion);
	printf("journalInfoBlock = 0x%x\n", header->journalInfoBlock);
	printf("createDate = 0x%x\n", header->createDate);
	printf("modifyDate = 0x%x\n", header->modifyDate);
	printf("backupDate = 0x%x\n", header->backupDate);
	printf("checkedDate = 0x%x\n", header->checkedDate);
	printf("fileCount = 0x%x\n", header->fileCount);
	printf("folderCount = 0x%x\n", header->folderCount);
	printf("blockSize = 0x%x\n", header->blockSize);
	printf("totalBlocks = 0x%x\n", header->totalBlocks);
	printf("freeBlocks = 0x%x\n", header->freeBlocks);
	printf("nextAllocation = 0x%x\n", header->nextAllocation);
	printf("rsrcClumpSize = 0x%x\n", header->rsrcClumpSize);
	printf("dataClumpSize = 0x%x\n", header->dataClumpSize);
	printf("nextCatalogID = 0x%x\n", header->nextCatalogID);
	printf("writeCount = 0x%x\n", header->writeCount);
	printf("encodingsBitmap = 0x%x\n", header->encodingsBitmap);

	printForkData(&header->allocationFile);
	printForkData(&header->extentsFile);
	printForkData(&header->catalogFile);
	printForkData(&header->attributesFile);
	printForkData(&header->startupFile);
}

void printForkData(HFSPlusForkData* forkData) {
	printf("logicalSize = 0x%x\n", forkData->logicalSize);
	printf("clumpSize = 0x%x\n", forkData->clumpSize);
	printf("totalBlocks = 0x%x\n", forkData->totalBlocks);
	printExtentRecord(&forkData->extents);
}

void printExtentRecord(HFSPlusExtentRecord* extentRecord) {
  HFSPlusExtentDescriptor *extentDescriptor;
  extentDescriptor = (HFSPlusExtentDescriptor*)extentRecord;

  printExtentDescriptor(&extentDescriptor[0]);
  printExtentDescriptor(&extentDescriptor[1]);
  printExtentDescriptor(&extentDescriptor[2]);
  printExtentDescriptor(&extentDescriptor[3]);
  printExtentDescriptor(&extentDescriptor[4]);
  printExtentDescriptor(&extentDescriptor[5]);
  printExtentDescriptor(&extentDescriptor[6]);
  printExtentDescriptor(&extentDescriptor[7]);
}

void printExtentDescriptor(HFSPlusExtentDescriptor* extentDescriptor) {
  printf("startBlock = 0x%x\n", extentDescriptor->startBlock);
  printf("blockCount = 0x%x\n", extentDescriptor->blockCount);
}

void printNodeDescriptor(BTNodeDescriptor* node) {
	printf("fLink = 0x%x\n", node->fLink);
	printf("bLink = 0x%x\n", node->bLink);
	printf("kind = 0x%x\n", node->kind);
	printf("height = 0x%x\n", node->height);
	printf("numRecords = 0x%x\n", node->numRecords);
	printf("reserved = 0x%x\n", node->reserved);
}

void printBTHeaderRec(BTHeaderRec* header) {
	printf("treeDepth = 0x%x\n", header->treeDepth);
	printf("rootNode = 0x%x\n", header->rootNode);
	printf("leafRecords = 0x%x\n", header->leafRecords);
	printf("firstLeafNode = 0x%x\n", header->firstLeafNode);
	printf("lastLeafNode = 0x%x\n", header->lastLeafNode);
	printf("nodeSize = 0x%x\n", header->nodeSize);
	printf("maxKeyLength = 0x%x\n", header->maxKeyLength);
	printf("totalNodes = 0x%x\n", header->totalNodes);
	printf("freeNodes = 0x%x\n", header->freeNodes);
	printf("clumpSize = 0x%x\n", header->clumpSize);
	printf("attributes = 0x%x\n", header->attributes);
}

void printBSDInfo(HFSPlusBSDInfo* info) {
	printf("ownerID = 0x%x\n", info->ownerID);
	printf("groupID = 0x%x\n", info->groupID);
	printf("fileMode = 0x%x\n", info->fileMode);
	printf("special = 0x%x\n", info->special);
}

void printPoint(Point* point) {
	printf("v = 0x%x\n", point->v);
	printf("h = 0x%x\n", point->h);
}

void printRect(Rect* rect) {
	printf("top = 0x%x\n", rect->top);
	printf("left = 0x%x\n", rect->left);
	printf("bottom = 0x%x\n", rect->bottom);
	printf("right = 0x%x\n", rect->right);
}

void printFolderInfo(FolderInfo* info) {
	printRect(&info->windowBounds);
	printf("finderFlags = 0x%x\n", info->finderFlags);
	printPoint(&info->location);
}

void printExtendedFolderInfo(ExtendedFolderInfo* info) {
	printPoint(&info->scrollPosition);
	printf("extendedFinderFlags = 0x%x\n", info->extendedFinderFlags);
	printf("putAwayFolderID = 0x%x\n", info->putAwayFolderID);
}

void printFileInfo(FileInfo* info) {
	printf("fileType = 0x%x\n", info->fileType);
	printf("fileCreator = 0x%x\n", info->fileCreator);
	printf("finderFlags = 0x%x\n", info->finderFlags);
	printPoint(&info->location);
}

void printExtendedFileInfo(ExtendedFileInfo* info) {
	printf("extendedFinderFlags = 0x%x\n", info->extendedFinderFlags);
	printf("putAwayFolderID = 0x%x\n", info->putAwayFolderID);
}

void printCatalogFolder(HFSPlusCatalogFolder* record) {
	printf("recordType = 0x%x\n", record->recordType);
	printf("flags = 0x%x\n", record->flags);
	printf("valence = 0x%x\n", record->valence);
	printf("folderID = 0x%x\n", record->folderID);
	printf("createDate = 0x%x\n", record->createDate);
	printf("contentModDate = 0x%x\n", record->contentModDate);
	printf("attributeModDate = 0x%x\n", record->attributeModDate);
	printf("accessDate = 0x%x\n", record->accessDate);
	printf("backupDate = 0x%x\n", record->backupDate);

	printBSDInfo(&record->permissions);
	printFolderInfo(&record->userInfo);
	printExtendedFolderInfo(&record->finderInfo);

	printf("textEncoding = 0x%x\n", record->textEncoding);
	printf("folderCount = 0x%x\n", record->folderCount);
}

void printCatalogFile(HFSPlusCatalogFile* record) {
	printf("recordType = 0x%x\n",record->recordType);
	printf("flags = 0x%x\n", record->flags);
	printf("fileID = 0x%x\n", record->fileID);
	printf("createDate = 0x%x\n", record->createDate);
	printf("contentModDate = 0x%x\n", record->contentModDate);
	printf("attributeModDate = 0x%x\n", record->attributeModDate);
	printf("record->accessDate = 0x%x\n", record->accessDate);
	printf("backupDate = 0x%x\n", record->backupDate);

	printBSDInfo(&record->permissions);
	printFileInfo(&record->userInfo);
	printExtendedFileInfo(&record->finderInfo);

	printf("textEncoding = 0x%x\n", record->textEncoding);

	printForkData(&record->dataFork);
	printForkData(&record->resourceFork);
}

