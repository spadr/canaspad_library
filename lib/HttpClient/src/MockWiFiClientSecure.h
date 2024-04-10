// MockWiFiClientSecure.h

#include <Arduino.h>

/**
 * このクラスは、WiFiClientSecureのモック実装を提供する。
 * 実際のネットワーク接続は行わず、事前定義されたレスポンスを模擬的に返す。
 * 主にテスト目的や開発中のプロトタイピングに使用する。
 */
class WiFiClientSecure {
  private:
    int count = 0;       // 次に読むべきres内の位置
    int lastReadPos = 0; // 最後に読んだ位置
    // 事前定義されたHTTPレスポンスメッセージ
    String res = "HTTP/1.1 404 Not Found\r\n"
                 "Content-Type: text/plain\r\n"
                 "Content-Length: 13\r\n"
                 "\r\n"
                 "404 Not Found";

  public:
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
     * HTTPリクエストに基づいてレスポンスメッセージを設定する。
     * @param request HTTPリクエストの内容
     */
    void print(const String& request) {
        if (request.startsWith("GET /rest/v1/tube")) {
            res = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json\r\n"
                  "Content-Length: 47\r\n"
                  "\r\n"
                  "[{\"token\":\"6a78pana-4d87-964d-a325-f3377ea9e584\"}]";
        } else if (request.startsWith("POST /rest/v1/element")) {
            res = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json\r\n"
                  "Content-Length: 273\r\n"
                  "\r\n"
                  "[{\"id\":\"6a78pana-4d87-964d-a325-f3377ea9e584\",\"value\":2390.405273,"
                  "\"is_delete\":false,\"created_at\":\"2024-04-10T16:00:22\","
                  "\"user_id\":\"6a78pana-4d87-964d-a325-f3377ea9e584\","
                  "\"tube_token\":\"6a78pana-4d87-964d-a325-f3377ea9e584\","
                  "\"updated_at\":\"2024-04-10T07:00:27.036506\","
                  "\"token\":\"6a78pana-4d87-964d-a325-f3377ea9e584\"}]";
        } else if (request.startsWith("POST /auth/v1/token")) {
            res =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: 456\r\n"
                "\r\n"
                "{"
                "\"access_token\": "
                "\"eyJhbGunLiJIUcI1NiIsImtpZCI6InNsOTk0bTY3UmxJT1lVc3kiLCJ0eXAiOiJKV1QifQ."
                "eyJhdWQiJiJhdXRoZW50aWNhdGVkIiwiZXhwIjoxNzEyNzM2MDEwLCJpYXQiOjE3MTI3MzI0MTAsImlzcy"
                "I6Imh0dHBzOi8vem50cWpwaHZvc2N5aGtieWx0c3ouc3VwYWJhc2UuY28vYXV0aC92MSIsInN1YiI6IjI0"
                "M2M1ZThjLWMyBRgtNDRjZC04NjliLWIyZDk2NTE2Zjk2YiIsImVtYWlsIjoiaXUzMzIyMDAxQGhpcm9zYW"
                "tpLXUuYWMuanAiLCJwaG9uZSI6IiIsImFwcF9tZXRhZGF5HSI6eyJwcm92aNYlciI6ImVtYWlsIiwicHJv"
                "dmlkZXJzIjpbImVtYWlsIl19LCJ1c2VyX21ldGFkYXRhIjp7fSwicm9sZSI6ImF1dGhlbnRpY2F0ZWQiLC"
                "JhYWwiOiJhYWwxIiwiYW1yIjpbeyJtZXRob2QiLiJwYXNzd29yZCIsInRpbWVzdGFtcCI6MTcxMjczMjQx"
                "RG1dLCJzZXNzaW9uX2ljIjoiOWE2YjM5MWEtZDJiOC00OGY2LWE4ZDMtNjI0ZjFhMTk6YmRjIiwiaXNfYU"
                "5vbnltb3VzIjpmYWxzZX0.q2r7_Msu90J0CsEla6kX8ZCTCpcN6GgXIIlIqiYvHRJ\","
                "\"token_type\": \"bearer\","
                "\"expires_in\": 3600,"
                "\"expires_at\": 1712736010,"
                "\"refresh_token\": \"EysHhPLvUCd5ydXAao58rM\""
                "}";
        } else if (request.startsWith("GET /rest/v1/element")) {
            res = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json\r\n"
                  "Content-Length: 78\r\n"
                  "\r\n"
                  "[{\"value\":2390.405273,\"created_at\":\"2024-04-10T16:00:22\"}]";
        }
        count = 0; // レスポンスの読み取り開始位置をリセット
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
