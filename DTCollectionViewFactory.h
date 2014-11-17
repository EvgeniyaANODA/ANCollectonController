//
//  DTCollectionFactory.h
//  DTCollectionViewManagerExample
//
//  Created by Denys Telezhkin on 21.07.13.
//  Copyright (c) 2013 Denys Telezhkin. All rights reserved.

#import "DTModelTransfer.h"

/**
 Protocol, used by DTCollectionFactory to access collectionView property on DTCollectionViewController instance.
 */
@protocol DTCollectionFactoryDelegate

- (UICollectionView *)collectionView;

@end

/**
 `DTCollectionFactory` is a cell/supplementary view factory, that is used by DTCollectionViewController.
 
 This class is intended to be used internally by DTCollectionViewController. You shouldn't call any of it's methods.
 */

@interface DTCollectionViewFactory : NSObject

- (void)registerCellClass:(Class)cellClass
            forModelClass:(Class)modelClass;

- (void)registerSupplementaryClass:(Class)supplementaryClass
                           forKind:(NSString *)kind
                     forModelClass:(Class)modelClass;

- (UICollectionViewCell <DTModelTransfer> *)cellForItem:(id)modelItem
                                            atIndexPath:(NSIndexPath *)indexPath;

- (UICollectionReusableView <DTModelTransfer> *)supplementaryViewOfKind:(NSString *)kind
                                                                forItem:(id)modelItem
                                                            atIndexPath:(NSIndexPath *)indexPath;

@property (nonatomic, weak) id <DTCollectionFactoryDelegate> delegate;

@end
