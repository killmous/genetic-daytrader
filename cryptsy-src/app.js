var request = require('request'),
    sqlite3 = require('sqlite3'),
    db = new sqlite3.Database('test.db');

db.serialize(function() {
    db.run('                             \
        CREATE TABLE IF NOT EXISTS btc ( \
            id INTEGER(8),               \
            time VARCHAR(30),            \
            type VARCHAR(4),             \
            price VARCHAR(10),           \
            quantity VARCHAR(10),        \
            total VARCHAR(10)            \
        )                                \
    ');
    request('http://pubapi1.cryptsy.com/api.php?method=marketdata', function(error, response, body) {
        var pretty_data = JSON.parse(body)['return']['markets']['BTC/USD'];
        var btc = {
            name: pretty_data['primaryname'],
            code: pretty_data['primarycode'],
            trades: pretty_data['recenttrades']
        };
        for(var trade in btc['trades']) {
            var query = 'INSERT INTO btc (' +
                'id, time, type, price, quantity, total' +
            ') ' +
            'VALUES (' +
                '\'' + btc['trades'][trade]['id'] + '\', ' +
                '\'' + btc['trades'][trade]['time'] + '\', ' +
                '\'' + btc['trades'][trade]['type'] + '\', ' +
                '\'' + btc['trades'][trade]['price'] + '\', ' +
                '\'' + btc['trades'][trade]['quantity'] + '\', ' +
                '\'' + btc['trades'][trade]['total'] + '\'' +
            ')';
            db.run(query);
        }
        db.close();
    });
})