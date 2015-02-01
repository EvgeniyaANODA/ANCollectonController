//
//  ANCollectionViewControllerEvents.h
//  ANCollectionViewManagerExample
//
//  Created by Denys Telezhkin on 30.09.14.
//  Copyright (c) 2014 Denys Telezhkin. All rights reserved.
//


#import <Foundation/Foundation.h>

/**
 Protocol, that allows you to react to different ANCollectionViewController events. This protocol is adopted by ANCollectionViewController instance.
 */
@protocol ANCollectionViewControllerEvents <NSObject>

@optional

// updating content

/**
 This method will be called every time after storage contents changed, and just before UI will be updated with these changes.
 */
- (void)collectionControllerWillUpdateContent;

/**
 This method will be called every time after storage contents changed, and after UI has been updated with these changes.
 */
- (void)collectionControllerDidUpdateContent;

// searching

/**
 This method is called when ANCollectionViewController will start searching in current storage. After calling this method ANCollectionViewController starts using searchingDataStorage instead of dataStorage to provide search results.
 */
- (void)collectionControllerWillBeginSearch;

/**
 This method is called after ANCollectionViewController ended searching in storage and updated UITableView UI.
 */
- (void)collectionControllerDidEndSearch;

/**
 This method is called, when search string becomes empty. ANCollectionViewController switches to default storage instead of searchingDataStorage and reloads data of the UICollectionView.
 */
- (void)collectionControllerDidCancelSearch;

@end
