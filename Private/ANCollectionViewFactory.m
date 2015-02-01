//
//  ANCollectionFactory.m
//  ANCollectionViewManagerExample
//
//  Created by Denys Telezhkin on 21.07.13.
//  Copyright (c) 2013 Denys Telezhkin. All rights reserved.
//

#import "ANCollectionViewFactory.h"
#import "ANRuntimeHelper.h"

@interface ANCollectionViewFactory()

@property (nonatomic, strong) NSMutableDictionary * cellMappings;
@property (nonatomic, strong) NSMutableDictionary * supplementaryMappings;

@end

@implementation ANCollectionViewFactory

-(NSMutableDictionary *)cellMappings
{
    if (!_cellMappings)
    {
        _cellMappings = [NSMutableDictionary dictionary];
    }
    return _cellMappings;
}

-(NSMutableDictionary * )supplementaryMappings
{
    if (!_supplementaryMappings)
    {
        _supplementaryMappings = [NSMutableDictionary dictionary];
    }
    return _supplementaryMappings;
}

-(void)setSupplementaryClass:(Class)supplementaryClass forKind:(NSString *)kind forModelClass:(Class)modelClass
{
    NSMutableDictionary * kindMappings = self.supplementaryMappings[kind];
    if (!kindMappings)
    {
        kindMappings = [NSMutableDictionary dictionary];
        self.supplementaryMappings[kind] = kindMappings;
    }
    kindMappings[[ANRuntimeHelper modelStringForClass:modelClass]] = [ANRuntimeHelper classStringForClass:supplementaryClass];
}

- (void)registerCellClass:(Class)cellClass forModelClass:(Class)modelClass
{
    NSString * cellClassString = [ANRuntimeHelper classStringForClass:cellClass];
    
    [[self.delegate collectionView] registerClass:cellClass forCellWithReuseIdentifier:cellClassString];
    
    self.cellMappings[[ANRuntimeHelper modelStringForClass:modelClass]] = [ANRuntimeHelper classStringForClass:cellClass];
}

- (void)registerSupplementaryClass:(Class)supplementaryClass
                           forKind:(NSString *)kind
                     forModelClass:(Class)modelClass
{
    NSString * supplementaryClassString = [ANRuntimeHelper classStringForClass:supplementaryClass];

    [[self.delegate collectionView] registerClass:supplementaryClass
                       forSupplementaryViewOfKind:kind
                              withReuseIdentifier:supplementaryClassString];
    
    [self setSupplementaryClass:supplementaryClass forKind:kind forModelClass:modelClass];
}

- (UICollectionViewCell <ANModelTransfer> *)cellForItem:(id)modelItem
                                            atIndexPath:(NSIndexPath *)indexPath
{
    NSString * classString = self.cellMappings[[ANRuntimeHelper modelStringForClass:[modelItem class]]];
    return [[self.delegate collectionView]
                dequeueReusableCellWithReuseIdentifier:classString
                                          forIndexPath:indexPath];
}

- (UICollectionReusableView <ANModelTransfer> *)supplementaryViewOfKind:(NSString *)kind
                                                                forItem:(id)modelItem
                                                            atIndexPath:(NSIndexPath *)indexPath
{
    NSMutableDictionary * kindMappings = self.supplementaryMappings[kind];
    NSString * cellClassString  = kindMappings[[ANRuntimeHelper modelStringForClass:[modelItem class]]];
    if (!cellClassString)
    {
        return nil;
    }
    else
    {
        return [[self.delegate collectionView]
                dequeueReusableSupplementaryViewOfKind:kind
                                   withReuseIdentifier:cellClassString
                                          forIndexPath:indexPath];
    }
}

@end
