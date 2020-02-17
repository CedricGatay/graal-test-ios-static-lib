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
            self.doCallback(&cargs)
            /*two_way({ (result: AnyObject) in
                    print("result : \(result)")
            })*/
            //run_main(Int32(args.count), &cargs)
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


extension AppDelegate{


    func doCallback(_ cargs : inout [UnsafeMutablePointer<Int8>?]){
        /**
         * A better callback implementation.
         *
         * This one casts the void pointer to UnsafeMutablePointer<APIStruct>,
         * then uses its memory to construct an instance of APIStruct.  Even if
         * tight packing is used by the C code, the APIStruct will correctly
         * reflect the data placed there by the C code.  This is as long as
         * the pack pragma is available via the bridging header.
         *
         * It is called OneWayCallback because whatever changes it makes to
         * the APIStruct provided to it by C code won't be visible to the
         * C code.  This is because we modify a copy of the structure
         * populated by the C code.
         */
        let OneWayCallback : my_cb_t = {( p : Optional<UnsafeMutableRawPointer> )-> () in
            print( "In OneWayCallback(), received a pointer. " );
            let obj = String(cString: p!.assumingMemoryBound(to: CChar.self))
            let notification: Notification = Notification(name: NSNotification.Name(rawValue: "Test"), object: obj)
            NotificationCenter.default.post(notification)
            print(obj)
        }

        
        
        /**
         * Call the C API giving it the 1-way callback.
         */
        //run_graal()
        run_framework(OneWayCallback, Int32(cargs.count), &cargs)
        //CUseCallback( OneWayCallback, 1 )
    }
    
    
}

func testMessageStruct(message: EclairMessage) -> UnsafeMutablePointer<Message_Send_Struct>{
    let args = ["producer", "topic", "tags", "keys", message.json]
    let ptrs = args.map {strdup($0) }
    let res = Message_Send_Struct(producer_name: ptrs[0], topic: ptrs[1], tags: ptrs[2], keys: ptrs[3], body: ptrs[4])
   // ptrs.forEach { free($0) }
    print(res)
    let pointer = UnsafeMutablePointer<Message_Send_Struct>.allocate(capacity: 1)
    pointer.pointee = res
    return pointer
}

func freeStruct(ptr: UnsafeMutablePointer<Message_Send_Struct>){
    free(ptr.pointee.producer_name)
    free(ptr.pointee.topic)
    free(ptr.pointee.tags)
    free(ptr.pointee.keys)
    free(ptr.pointee.body)
    ptr.deallocate()
}
