#include "PoloniexClient.hpp"


std::string PoloniexClient::buildAndSendRequest(const std::string &endpoint, std::string &query) {

    //Create the request object
    Request r(endpoint, query);

    //Send the request and if success, return the response.
    if (r.sendRequest()) {
        return r.response;
    } else {
        return "FAIL";
    }

}

//================= PUBLIC API METHODS ===================

/*** Grab the current ticker for all markets ***/
std::string PoloniexClient::public_TickerRequest() {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "returnTicker");
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}


/***Returns the 24-hour volume for all markets, plus totals for primary currencies.***/
std::string PoloniexClient::public_VolumeRequest() {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "return24hVolume");
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}

std::string PoloniexClient::public_OrderBookRequest(std::string &pairs, int depth) {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "returnOrderBook");
    query.addQueryItem("currencyPair", QString::fromStdString(pairs));
    query.addQueryItem("depth", QString::number(depth));
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}

/**Takes Pairs and start and ending UNIX timestamps**/
std::string PoloniexClient::public_TradeHistory(std::string &pairs, int &start, int &end) {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "returnTradeHistory");
    query.addQueryItem("currencyPair", QString::fromStdString(pairs));
    query.addQueryItem("start", QString::number(start));
    query.addQueryItem("end", QString::number(end));
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}


/**Takes Pair and returns the most recent 200 trades in that market**/
std::string PoloniexClient::public_TradeHistory(std::string &pairs) {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "returnTradeHistory");
    query.addQueryItem("currencyPair", QString::fromStdString(pairs));
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}


/** Takes candlestick periods and start and end UNIX timestamps **/
/** Valid periods are 300, 900, 1800, 7200, 14400, and 86400 **/
std::string PoloniexClient::public_ChartData(std::string &pairs, int &period, int &start, int &end) {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "returnChartData");
    query.addQueryItem("currencyPair", QString::fromStdString(pairs));
    query.addQueryItem("period", QString::number(period));
    query.addQueryItem("start", QString::number(start));
    query.addQueryItem("end", QString::number(end));
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}

std::string PoloniexClient::public_Currencies() {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "returnCurrencies");
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}

std::string PoloniexClient::public_LoanOrders(std::string &coinSymbol) {
    //Construct the query.
    QUrlQuery query;
    query.addQueryItem("command", "returnLoanOrders");
    query.addQueryItem("currency", QString::fromStdString(coinSymbol));
    std::string encoded = query.query(QUrl::FullyEncoded).toUtf8().constData();

    return PoloniexClient::buildAndSendRequest(PoloniexClient::publicAPIEndpoint, encoded);
}




