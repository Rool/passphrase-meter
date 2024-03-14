// swift-tools-version:5.9

import PackageDescription

let package = Package(
    name: "WultraPassphraseMeter",
    platforms: [
        .iOS(.v12)
    ],
    products: [
        .library(name: "WultraPassphraseMeter", targets: ["WultraPassphraseMeter"]),
        .library(name: "WultraPassphraseMeterCore", targets: ["WultraPassphraseMeterCore"]),
        .library(name: "WultraPassphraseMeterCZSKDictionary", targets: ["WultraPassphraseMeterCZSKDictionary"]),
        .library(name: "WultraPassphraseMeterENDictionary", targets: ["WultraPassphraseMeterENDictionary"]),
        .library(name: "WultraPassphraseMeterRODictionary", targets: ["WultraPassphraseMeterRODictionary"])
    ],
    targets: [
        .binaryTarget(
            name: "WultraPassphraseMeter",
            url: "https://github.com/Rool/passphrase-meter/raw/swift59/distribution/WultraPassphraseMeter.xcframework.zip",
            checksum: "7a863f67ae548de280eb84ff087deaff9456931a03a618e630695f45620a308d"),
		//  swift package compute-checksum WultraPassphraseMeter.xcframework.zip 
        .binaryTarget(
            name: "WultraPassphraseMeterCore",
            url: "https://github.com/Rool/passphrase-meter/raw/swift59/distribution/WultraPassphraseMeterCore.xcframework.zip",
            checksum: "5b32bcf2d690f532e3bbc989dfeb27abde5ac3a8cbc910b703bfa235dd805a4e"),
        .binaryTarget(
            name: "WultraPassphraseMeterCZSKDictionary",
            url: "https://github.com/Rool/passphrase-meter/raw/swift59/distribution/WultraPassphraseMeterCZSKDictionary.xcframework.zip",
            checksum: "5f1d328557becb6d38048b883d32f650b881a8ee26c503f937a223bd6a746795"),
        .binaryTarget(
            name: "WultraPassphraseMeterENDictionary",
            url: "https://github.com/Rool/passphrase-meter/raw/swift59/distribution/WultraPassphraseMeterENDictionary.xcframework.zip",
            checksum: "4d1735b2be139b009e025aa0edd86dd00c22e4e77896eef070bde592742a5e1c"),
        .binaryTarget(
            name: "WultraPassphraseMeterRODictionary",
            url: "https://github.com/Rool/passphrase-meter/raw/swift59/distribution/WultraPassphraseMeterRODictionary.xcframework.zip",
            checksum: "5d32c024388b6378f4eb41b315b8a6ac06a7c25ab96153eb707c2f66588be0e0")
    ],
    swiftLanguageVersions: [.v5]
)
