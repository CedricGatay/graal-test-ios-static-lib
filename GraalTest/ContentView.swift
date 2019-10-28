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
    var body: some View {
        VStack{
            TextField("A", text: $a)
            TextField("B", text: $b)
            Text("Result : \(result)")
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
        
    func compute() -> Int{
        guard let a = Int(a), let b = Int(b) else { return 0 }
        return Int(azeqsd_graal_method(Int32(a), Int32(b)))
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
