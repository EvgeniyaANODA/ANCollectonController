//
//  ANCollectionViewController.h
//  ANCollectionViewManager
//
//  Created by Denys Telezhkin on 6/19/12.
//  Copyright (c) 2013 Denys Telezhkin. All rights reserved.


#import "ANMemoryStorage+ANCollectionViewManagerAdditions.h"
#import "ANStorageInterface.h"
#import "ANCollectionViewControllerEvents.h"

/**
 `ANCollectionViewController` manages all `UICollectionView` datasource methods and provides API for mapping your data models to UICollectionViewCells. It also contains storage object, that is responsible for providing data models.
 */

@interface ANCollectionController : NSObject
<
    UICollectionViewDataSource,
    UICollectionViewDelegate,
    UISearchBarDelegate,
    ANCollectionViewControllerEvents
>

///---------------------------------------
/// @name Properties
///---------------------------------------

@property (nonatomic, weak) UICollectionView * collectionView;
@property (nonatomic, weak) UISearchBar * searchBar;

@property (nonatomic, strong) id <ANStorageInterface> storage;
@property (nonatomic, strong) id <ANStorageInterface> searchingStorage;

- (instancetype)initWithCollectionView:(UICollectionView*)collectionView;

- (ANMemoryStorage *)memoryStorage;

- (void)registerCellClass:(Class)cellClass forModelClass:(Class)modelClass;

- (void)registerSupplementaryClass:(Class)supplementaryClass
                          forKind:(NSString *)kind
                    forModelClass:(Class)modelClass;

- (void)registerHeaderClass:(Class)headerClass forModelClass:(Class)modelClass;
- (void)registerFooterClass:(Class)footerClass forModelClass:(Class)modelClass;

///---------------------------------------
/// @name Search
///---------------------------------------

/**
 Filter presented table items, using searchString as a criteria. Current storage is queried with `searchingStorageForSearchString:inSearchScope:` method. If searchString is not empty, UICollectionViewDatasource is assigned to searchingStorage and collection view is reloaded automatically.
 
 @param searchString Search string used as a criteria for filtering.
 */
- (void)filterModelsForSearchString:(NSString *)searchString;

/**
 Filter presented table items, using searchString as a criteria. Current storage is queried with `searchingStorageForSearchString:inSearchScope:` method. If searchString or scopeNumber is not empty, UICollectionViewDatasource is assigned to searchingStorage and collection view is reloaded automatically.
 
 @param searchString Search string used as a criteria for filtering.
 
 @param scopeNumber Scope number of UISearchBar
 */
- (void)filterModelsForSearchString:(NSString *)searchString
                           inScope:(NSInteger)scopeNumber;

/**
 Returns whether search is active, based on current searchString and searchScope, retrieved from UISearchBarDelegate methods.
 */

- (BOOL)isSearching NS_REQUIRES_SUPER;

/**
 Perform animated update on UICollectionView. It can be used for complex animations, that should be run simultaneously. For example, `ANCollectionViewManagerAdditions` category on `ANMemoryStorage` uses it to implement moving items between indexPaths.
 
 @param animationBlock animation block to run on UICollectionView.
 */
- (void)performAnimatedUpdate:(void (^)(UICollectionView *))animationBlock;

@end
