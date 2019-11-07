//
//  AppDelegate.swift
//  GraalTest
//
//  Created by Cedric Gatay on 25/10/2019.
//  Copyright © 2019 Code-Troopers. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {



    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        let queue = DispatchQueue.init(label: "background")
        queue.async {
            print("AZEAZEAZEAZ")
            guard let fileURL = Bundle.main.url(forResource:"libsecp256k1", withExtension: "dylib")
                else {
                    print("Unable to get path of app")
                    return
            }
            var components = fileURL.pathComponents
            components.removeLast()
            components.removeFirst()
            let path =  components.joined(separator: "/")

            let args = ["",
                        "-Djava.library.path=/\(path)",
                        "-Djava.home=/\(path)",
                        "-Djava.vm.vendor=The Android Project",
                        "-Djavax.net.ssl.trustStore=/\(path)/lib/security/cacerts"
            ]

            // Create [UnsafeMutablePointer<Int8>]:
            var cargs = args.map { strdup($0) }
            run_main(Int32(args.count), &cargs)
            for ptr in cargs { free(ptr) }
        }
        
        //graal_method()
    
        return true
    }

    // MARK: UISceneSession Lifecycle

    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to thecongé discarded scenes, as they will not return.
    }


}

