//
//  ContentView.swift
//  GraalTest
//
//  Created by Cedric Gatay on 25/10/2019.
//  Copyright © 2019 Code-Troopers. All rights reserved.
//

import SwiftUI

struct ContentView: View {
    @State var result: Int = 0
    @State var a: String = ""
    @State var b: String = ""
    @ObservedObject var logMsg: LogMsg = LogMsg()
    
    
    var body: some View {
        ScrollView{
        VStack{
            TextField("A", text: $a)
            TextField("B", text: $b)
            Text("Result : \(result)")
            Text("LogMsg : \(logMsg.msg)")
            Text("LogMsg : \(logMsg.eclairMsg)")
            Button(action: {self.result = self.compute()}) {
                Text("Combien").padding()
            }
            Button(action: {
                let msg = testMessageStruct(message: EclairMessage(
                        switchServer: SwitchServer(uri: "03933884aaf1d6b108397e5efe5c86bcf2d8ca8d2f700eda99db9214fc2712b134@34.250.234.192:9735")
                    )
                )
                bridge_send_message(msg)
                freeStruct(ptr: msg)
            }) {
                Text("Start").padding()
            }
            Button(action: {stop_method()}) {
                Text("Stop").padding()
            }
        }
        }
    }
        
    func compute() -> Int{
        guard let a = Int(a), let b = Int(b) else { return 0 }
        return Int(azeqsd_graal_method(Int32(a), Int32(b)))
    }
}

class LogMsg: ObservableObject{
    @Published var msg: String = ""
    @Published var eclairMsg: String = ""
    
    init(){
        NotificationCenter.default.addObserver(self, selector: #selector(onChange(_:)), name: NSNotification.Name(rawValue: "Test"), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(onEclairToNative(_:)), name: NSNotification.Name(rawValue: "EclairToNative"), object: nil)
    }
    
    @objc func onChange(_ sender: NSNotification){
        DispatchQueue.main.async {
            self.msg += "\n" + (sender.object as? String ?? "N/A")
        }
    }
    
    @objc func onEclairToNative(_ sender: NSNotification){
        DispatchQueue.main.async {
            self.eclairMsg += "\n" + (sender.object as? String ?? "N/A")
        }
    }
    
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
