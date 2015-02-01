//
//  ANMemoryStorage+ANCollectionViewManagerAdditions.h
//  ANCollectionViewManagerExample
//
//  Created by Denys Telezhkin on 21.08.14.
//  Copyright (c) 2014 Denys Telezhkin. All rights reserved.
//

#import "ANMemoryStorage.h"

/**
 Category, that adds UICollectionView specific methods to ANMemoryStorage.
 */

@interface ANMemoryStorage (ANCollectionViewManagerAdditions)

/**
 Move collection item to `indexPath`.
 
 @param sourceIndexPath source indexPath of item to move.
 
 @param destinationIndexPath Index, where item should be moved.
 
 @warning Moving item at index, that is not valid, won't do anything, except logging into console about failure
 */
-(void)moveCollectionItemAtIndexPath:(NSIndexPath *)sourceIndexPath
                         toIndexPath:(NSIndexPath *)destinationIndexPath;

///---------------------------------------
/// @name Managing sections
///---------------------------------------

/**
 Moves a section to a new location in the collection view. Supplementary models are moved automatically.
 
 @param fromSection The index of the section to move.
 
 @param toSection The index in the collection view that is the destination of the move for the section. The existing section at that location slides up or down to an adjoining index position to make room for it.
 */
-(void)moveCollectionViewSection:(NSInteger)fromSection toSection:(NSInteger)toSection;

@end
