// MockWiFiClientSecure.h

#include <Arduino.h>

/**
 * このクラスは、WiFiClientSecureのモック実装を提供する。
 * 実際のネットワーク接続は行わず、事前定義されたレスポンスを模擬的に返す。
 * 主にテスト目的や開発中のプロトタイピングに使用する。
 */
class WiFiClientSecure {
  public:
    int count = 0;       // 次に読むべきres内の位置
    int lastReadPos = 0; // 最後に読んだ位置
    // 事前定義されたHTTPレスポンスメッセージ
    String res = "HTTP/1.1 200 OK\r\n"
                 "Content-Type: application/json\r\n"
                 "Content-Length: 578\r\n"
                 "\r\n"
                 "[{\"token\":\"bac4b374-db34-42b3-b6f1-3fe13c342c47\",\"value\":\"1.23\","
                 "\"created_at\":\"2024-04-09 07:07:30.444541\",\"file_name\":\"39184367-f291-471e"
                 "-9648-0203f46f777a\",\"user_id\":\"36584317-f291-471e-9648-0203f46f777a\","
                 "\"file_path\":\"image/36584377-f291-471e-9648-0203f46f777a\",\"stored_in\":"
                 "\"iot.canaspad.net/storage/v1\",\"is_delete\":\"FALSE\"},{\"token\":"
                 "\"bac4b274-db34-42b3-b6f1-3fe13c392c47\",\"value\":\"1.23\",\"created_at\":"
                 "\"2024-04-09 07:07:30.444541\",\"file_name\":\"39684367-f291-471e-9648-0203f46f7"
                 "77a\",\"user_id\":\"86584377-f291-471e-9642-0203f46f777a\",\"file_path\":"
                 "\"image/36584377-f291-471e-9648-0203f46f777a\",\"stored_in\":\"iot.canaspad.net/"
                 "storage/v1\",\"is_delete\":\"FALSE\"}]";

    /**
     * サーバー証明書を設定する。
     * @param root_ca サーバーのルートCA証明書
     */
    void setCACert(const char* root_ca) { /* 何もしない */
    }

    /**
     * クライアント証明書を設定する。
     * @param client_cert クライアント証明書
     */
    void setCertificate(const char* client_cert) { /* 何もしない */
    }

    /**
     * クライアントの秘密鍵を設定する。
     * @param client_key クライアントの秘密鍵
     */
    void setPrivateKey(const char* client_key) { /* 何もしない */
    }

    /**
     * セキュア接続の検証を無視する。
     */
    void setInsecure() { /* 何もしない */
    }

    /**
     * ホストに接続を試みる。（常に接続成功を模倣する）
     * @param host 接続先のホスト名
     * @param port 接続先のポート番号
     * @return 常にtrueを返する。
     */
    bool connect(const char* host, uint16_t port) {
        return true; // 常に接続成功を模倣
    }

    /**
     * 接続がまだ有効かどうかを確認する。（常に接続済みを模倣する）
     * @return 常にtrueを返する。
     */
    bool connected() {
        return true; // 常に接続済みを模倣
    }

    /**
     * データを送信する。
     * @param s 送信するデータ
     */
    void print(const String& s) {
        // 書き込み動作を模倣
    }

    /**
     * バイナリデータを送信する。
     * @param buf 送信するバイトデータ
     * @param size 送信するデータのサイズ
     */
    void write(const uint8_t* buf, size_t size) {
        // 書き込み動作を模倣
    }

    /**
     * まだ読み取り可能なデータがあるかどうかを確認する。
     * @return データがある場合は1、ない場合は0を返す。
     */
    int available() {
        // resの残りがあるかチェック
        return count < res.length() ? 1 : 0;
    }

    /**
     * HTTPメッセージからterminator文字までの文字列を読み取る。
     * @param terminator 終端文字
     * @return terminatorまでの文字列。もしくは、最後まで読み取った場合の文字列。
     */
    String readStringUntil(char terminator) {
        String result = "";
        bool foundTerminator = false;

        // resの残りを読む
        for (; count < res.length(); ++count) {
            char c = res[count];
            if (c == terminator) {
                foundTerminator = true;
                ++count; // terminatorの次の位置に進める
                break;
            }
            result += c;
        }

        if (foundTerminator || (!foundTerminator && result.length() > 0)) {
            // terminatorが見つかった、または最後の文字列を返す場合
            return result;
        } else {
            // 読むべきものがない場合
            return "";
        }
    }

    /**
     * 接続を閉じる。
     */
    void stop() { /* 何もしない */
    }
};
