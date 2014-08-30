var request = require('request'),
    sqlite3 = require('sqlite3'),
    db = new sqlite3.Database('btc.db');

function averageObjectArray(array, element) {
    var sum = 0;
    var len = 0;
    array.forEach(function(value) {
        sum += parseFloat(value[element]);
        len++;
    });
    return sum/len;
}

function maxObjectArray(array, element) {
    var max = 0;
    array.forEach(function(value) {
        if(parseFloat(value[element]) > max) {
            max = parseFloat(value[element]);
        }
    });
    return max;
}

function minObjectArray(array, element) {
    var min = array[0][element];
    array.forEach(function(value) {
        if(parseFloat(value[element]) < min) {
            min = parseFloat(value[element]);
        }
    });
    return min;
}

db.serialize(function() {
    /*
     * Multiline strings are just so hard to implement
     * amiright @javascript
     */
    process.stdout.write('Initializing sqlite3 table...');
    db.run(
        'CREATE TABLE IF NOT EXISTS btc (' +
            'time VARCHAR(30), ' +
            'avg VARCHAR(10), ' +
            'max VARCHAR(10), ' +
            'min VARCHAR(10) ' +
        ')'
    );
    console.log('done!');

    /*
     * I swear this shit takes like 4 days to respond
     */
    process.stdout.write('Starting request to Cryptsy...');
    request('http://pubapi1.cryptsy.com/api.php?method=marketdata', function(error, response, body) {
        console.log('done!');
        process.stdout.write('Processing data into properly-formatted JSON...');
        var pretty_data = JSON.parse(body)['return']['markets']['BTC/USD'];
        var btc = {
            name: pretty_data['primaryname'],
            code: pretty_data['primarycode'],
            trades: pretty_data['recenttrades']
        };
        var hours = [];
        var hourly_trades_raw = [];
        var hourly_trades = [];

        /*
         * Prepare yourself, brave soldier, for the wall of loops
         * May you iterate in peace
         */
        for(var trade in btc['trades']) {
            var date = new Date(btc['trades'][trade]['time'].split(' ').join('T'))
            btc['trades'][trade]['time'] = Math.round((date.getTime() / 1000)/3600)*3600;
            if(hours.indexOf(btc['trades'][trade]['time']) < 0) {
                hours.push(btc['trades'][trade]['time']);
            }
        }
        for(var hour in hours) {
            hourly_trades_raw.push(btc['trades'].filter(function(value) {
                return value['time'] == hours[hour];
            }));
        }
        hourly_trades_raw.forEach(function(trades) {
            var trade = {};
            if(trades.length != 1) {
                trade = {
                    time: trades[0]['time'],
                    avg: averageObjectArray(trades, 'price'),
                    max: maxObjectArray(trades, 'price'),
                    min: minObjectArray(trades, 'price')
                };
            } else {
                trade = {
                    time: trades[0]['time'],
                    avg: trades[0]['price'],
                    max: trades[0]['price'],
                    min: trades[0]['price']
                };
            }
            hourly_trades.push(trade);
        });
        console.log('done!');
        process.stdout.write('Writing to database...');
        for(var trade in hourly_trades) {
            var query = 'INSERT INTO btc (' +
                'time, avg, max, min' +
            ') ' +
            'VALUES (' +
                '\'' + hourly_trades[trade]['time'] + '\', ' +
                '\'' + hourly_trades[trade]['avg'] + '\',' +
                '\'' + hourly_trades[trade]['max'] + '\',' +
                '\'' + hourly_trades[trade]['min'] + '\'' +
            ')';
            db.run(query);
        }
        console.log('done!');
        db.close();
    });
});