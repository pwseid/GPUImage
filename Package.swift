// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "GPUImage",
    platforms: [
        .iOS(.v9)
    ],
    products: [
        .library(
            name: "GPUImage",
            targets: ["GPUImage"]
        )
    ],
    targets: [
        .target(
            name: "GPUImage",
            path: "framework",
            exclude: [
                "Source/Mac",
                "Source/iOS/Framework",
                "Source/iOS/GPUImage-Prefix.pch"
            ],
            sources: [
                "Source"
            ],
            resources: [
                .process("Resources")
            ],
            publicHeadersPath: "Source/include",
            cSettings: [
                .headerSearchPath("Source"),
                .headerSearchPath("Source/iOS")
            ],
            linkerSettings: [
                .linkedFramework("AVFoundation"),
                .linkedFramework("CoreMedia"),
                .linkedFramework("CoreVideo"),
                .linkedFramework("OpenGLES"),
                .linkedFramework("QuartzCore"),
                .linkedFramework("UIKit")
            ]
        )
    ]
)
