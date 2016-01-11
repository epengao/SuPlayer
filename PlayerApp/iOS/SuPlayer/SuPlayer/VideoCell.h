//
//  MovieListCell.h
//  SuPlayer
//
//  Created by Kortide on 15/11/4.
//  Copyright © 2015年 EC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface VideoFileCell : UITableViewCell
- (void)setCellContent: (NSString*)filePath withFileName:(NSString*)fileName;
@end
