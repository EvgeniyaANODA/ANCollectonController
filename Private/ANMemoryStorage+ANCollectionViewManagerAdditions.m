//
//  ANMemoryStorage+ANCollectionViewManagerAdditions.m
//  ANCollectionViewManagerExample
//
//  Created by Denys Telezhkin on 21.08.14.
//  Copyright (c) 2014 Denys Telezhkin. All rights reserved.
//


#import "ANMemoryStorage+ANCollectionViewManagerAdditions.h"
#import "ANCollectionViewControllerEvents.h"
#import "ANLogger.h"

@interface ANMemoryStorage()

@property (nonatomic, retain) ANStorageUpdate * currentUpdate;

// private methods and properties on ANMemoryStorage, that we need access in this class
-(ANSectionModel *)getValidSection:(NSUInteger)sectionNumber;

-(void)startUpdate;
-(void)finishUpdate;

@end

@protocol ANCollectionViewStorageUpdating <ANStorageUpdatingInterface>

-(void)performAnimatedUpdate:(void(^)(UICollectionView *))animationBlock;

@end

@implementation ANMemoryStorage(ANCollectionViewManagerAdditions)

-(void)moveCollectionItemAtIndexPath:(NSIndexPath *)sourceIndexPath
                         toIndexPath:(NSIndexPath *)destinationIndexPath;
{
    [self startUpdate];
    
    id item = [self objectAtIndexPath:sourceIndexPath];
    
    if (!sourceIndexPath || !item)
    {
        ANLogWarning(@"ANCollectionViewManager: source indexPath should not be nil when moving collection item");
        return;
    }
    ANSectionModel * sourceSection = [self getValidSection:sourceIndexPath.section];
    ANSectionModel * destinationSection = [self getValidSection:destinationIndexPath.section];
    
    if ([destinationSection.objects count] < destinationIndexPath.row)
    {
        
        ANLogWarning(@"ANCollectionViewManager: failed moving item to indexPath: %@, only %@ items in section",destinationIndexPath,@([destinationSection.objects count]));
        self.currentUpdate = nil;
        return;
    }
    
    [(id<ANCollectionViewStorageUpdating>)self.delegate performAnimatedUpdate:^(UICollectionView *collectionView) {
        NSMutableIndexSet * sectionsToInsert = [NSMutableIndexSet indexSet];
        [self.currentUpdate.insertedSectionIndexes enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL *stop) {
            if ([collectionView numberOfSections] <= idx)
            {
                [sectionsToInsert addIndex:idx];
            }
        }];
        [collectionView performBatchUpdates:^{
            [collectionView insertSections:sectionsToInsert];
        } completion:nil];
        
        [sourceSection.objects removeObjectAtIndex:sourceIndexPath.row];
        [destinationSection.objects insertObject:item
                                         atIndex:destinationIndexPath.row];
        
        if (sourceIndexPath.item == 0 && sourceSection.objects.count == 0)
        {
            [collectionView reloadData];
        }
        else {
            [collectionView performBatchUpdates:^{
                [collectionView moveItemAtIndexPath:sourceIndexPath
                                        toIndexPath:destinationIndexPath];
            } completion:nil];
        }
    }];
    
    self.currentUpdate = nil;
}

-(void)moveCollectionViewSection:(NSInteger)fromSection toSection:(NSInteger)toSection
{
    [self startUpdate];
    ANSectionModel * validSectionFrom = [self getValidSection:fromSection];
    [self getValidSection:toSection];
    
    [self.currentUpdate.insertedSectionIndexes removeIndex:toSection];
    
    [(id<ANCollectionViewStorageUpdating>)self.delegate performAnimatedUpdate:^(UICollectionView * collectionView) {
        if (self.sections.count > collectionView.numberOfSections)
        {
            //Section does not exist, moving section causes many sections to change, so we just reload
            [collectionView reloadData];
        }
        else {
            [collectionView performBatchUpdates:^{
                [collectionView insertSections:self.currentUpdate.insertedSectionIndexes];
                [self.sections removeObjectAtIndex:fromSection];
                [self.sections insertObject:validSectionFrom atIndex:toSection];
                [collectionView moveSection:fromSection toSection:toSection];
            } completion:nil];
        }
    }];
    self.currentUpdate = nil;
}

@end
