#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIImage GPUImagePlatformImage;
#else
#import <Cocoa/Cocoa.h>
typedef NSImage GPUImagePlatformImage;
#endif

NS_INLINE GPUImagePlatformImage *GPUImageImageAtPath(NSString *path)
{
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
    return [UIImage imageWithContentsOfFile:path];
#else
    return [[NSImage alloc] initWithContentsOfFile:path];
#endif
}

NS_INLINE GPUImagePlatformImage *GPUImageLoadImageNamed(NSString *resourceName)
{
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
    GPUImagePlatformImage *image = [UIImage imageNamed:resourceName];
#else
    GPUImagePlatformImage *image = [NSImage imageNamed:resourceName];
#endif
    if (image != nil)
    {
        return image;
    }

    NSString *resourceBaseName = [resourceName stringByDeletingPathExtension];
    NSString *resourceExtension = [resourceName pathExtension];

    for (NSBundle *bundle in [NSBundle allBundles])
    {
        NSString *resourcePath = [bundle pathForResource:resourceBaseName ofType:resourceExtension];
        if (resourcePath == nil)
        {
            continue;
        }

        image = GPUImageImageAtPath(resourcePath);
        if (image != nil)
        {
            return image;
        }
    }

    for (NSBundle *bundle in [NSBundle allFrameworks])
    {
        NSString *resourcePath = [bundle pathForResource:resourceBaseName ofType:resourceExtension];
        if (resourcePath == nil)
        {
            continue;
        }

        image = GPUImageImageAtPath(resourcePath);
        if (image != nil)
        {
            return image;
        }
    }

    return nil;
}
