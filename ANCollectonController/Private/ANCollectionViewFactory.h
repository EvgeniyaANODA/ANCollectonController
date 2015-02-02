//
//  ANCollectionFactory.h
//  ANCollectionViewManagerExample
//
//  Created by Denys Telezhkin on 21.07.13.
//  Copyright (c) 2013 Denys Telezhkin. All rights reserved.
//

#import "ANModelTransfer.h"

/**
 Protocol, used by ANCollectionFactory to access collectionView property on ANCollectionViewController instance.
 */
@protocol ANCollectionFactoryDelegate

- (UICollectionView *)collectionView;

@end

/**
 `ANCollectionFactory` is a cell/supplementary view factory, that is used by ANCollectionViewController.
 
 This class is intended to be used internally by ANCollectionViewController. You shouldn't call any of it's methods.
 */

@interface ANCollectionViewFactory : NSObject

- (void)registerCellClass:(Class)cellClass
            forModelClass:(Class)modelClass;

- (void)registerSupplementaryClass:(Class)supplementaryClass
                           forKind:(NSString *)kind
                     forModelClass:(Class)modelClass;

- (UICollectionViewCell <ANModelTransfer> *)cellForItem:(id)modelItem
                                            atIndexPath:(NSIndexPath *)indexPath;

- (UICollectionReusableView <ANModelTransfer> *)supplementaryViewOfKind:(NSString *)kind
                                                                forItem:(id)modelItem
                                                            atIndexPath:(NSIndexPath *)indexPath;

@property (nonatomic, weak) id <ANCollectionFactoryDelegate> delegate;
@end
