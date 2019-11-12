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
        List{
        VStack{
            TextField("A", text: $a)
            TextField("B", text: $b)
            Text("Result : \(result)")
            Text("LogMsg : \(logMsg.msg)")
            Button(action: {self.result = self.compute()}) {
                Text("Combien")
            }
            Button(action: { start_method() }) {
                Text("Start")
            }
            Button(action: {stop_method()}) {
                Text("Stop")
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
    
    init(){
        NotificationCenter.default.addObserver(self, selector: #selector(onChange(_:)), name: NSNotification.Name(rawValue: "Test"), object: nil)
    }
    
    @objc func onChange(_ sender: NSNotification){
        DispatchQueue.main.async {
            self.msg += "\n" + (sender.object as? String ?? "N/A")
        }
    }
    
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
