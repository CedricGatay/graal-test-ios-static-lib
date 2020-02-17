import Foundation

struct EclairMessage{
    let switchServer: SwitchServer?
}

struct SwitchServer: Codable{
    let uri: String
}

extension EclairMessage: Codable{
    
    var json: String?{
        let encoder = JSONEncoder()
        guard let data = try? encoder.encode(self) else { return nil }
        return String(data: data, encoding: .utf8)
    }
}


