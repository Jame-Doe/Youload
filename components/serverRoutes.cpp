#include "server.hpp"
#include <crow/http_request.h>
#include <crow/mustache.h>

Server::Server() {
    CROW_ROUTE(app, "/") ([]() {
        return crow::mustache::load("index.html").render();
    });

    CROW_ROUTE(app, "/static/<string>") ([](std::string filename) {
        crow::response response;
        response.set_static_file_info("static/" + filename);
        return response;
    });

    CROW_ROUTE(app, "/youtube_link").methods(crow::HTTPMethod::POST) ([this](const crow::request &request) {
        auto json = crow::json::load(request.body);

        if (!json || !json.has("value") || !json.has("format")) {
            return crow::response(400, "JSON inválido.");
        }

        std::string link = json["value"].s();
        std::string format = json["format"].s();

        std::string filename = this->downloadFile(link, format);

        if (filename.empty()) {
            return crow::response(500, "Erro ao baixar vídeo do YouTube.");
        }

        crow::json::wvalue response;
        response["status"] = "success";
        response["fileUrl"] = "/get-file/" + filename;

        return crow::response(response);
    });

    CROW_ROUTE(app, "/get-file/<string>") ([](std::string filename) {
        crow::response res;

        res.set_static_file_info( "downloads/" + filename);
        res.add_header("Content-Disposition", "attachment; filename=\"downloads/" + filename + "\"");

        return res;
    });
}
