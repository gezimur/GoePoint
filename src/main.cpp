#include <iostream>
#include <thread>

#include <httpserver.hpp>

#include "RequestProcessor.h"

class Resources: public httpserver::http_resource
{
public:
    Resources()
    {
        geology::TemplateReader Reader("E:\\code\\GeologyServer\\resources");
        m_strJsSendForm = Reader.readTemplate("scripts\\SendForm.js");
        m_strJsLoadOrderList = Reader.readTemplate("scripts\\LoadOrderList.js");
        m_strJsLoadData = Reader.readTemplate("scripts\\ManagerDataScript.js");///@todo
        m_strCssResource = Reader.readTemplate("css\\MainCss.css");
    }

    const std::shared_ptr<httpserver::http_response> render(const httpserver::http_request& crReq)
    {
        auto strPath = crReq.get_path();
        if ("/resources/sendform.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsSendForm));
        if ("/resources/loadorderlist.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsLoadOrderList));
        if ("/resources/loaddata.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsLoadData));
        if ("/resources/maincss.css" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strCssResource, 200, "text/css"));

        return std::shared_ptr<httpserver::http_response>(new httpserver::http_response(404, "text/plain"));
    }

private:
    std::string m_strJsSendForm;
    std::string m_strJsLoadOrderList;
    std::string m_strCssResource;
    std::string m_strJsLoadData;
};

class Res404: public httpserver::http_resource
{
public:
    Res404()
        : m_Pages("E:\\code\\GeologyServer\\resources")
    {

    }

    const std::shared_ptr<httpserver::http_response> render(const httpserver::http_request& /*crReq*/)
    {
        return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_Pages.get404Page()));
    }

private:
    geology::PageContainer m_Pages;
};

int main()
{
    try
    {
        int iPort = 2345;

        httpserver::webserver WebServer = httpserver::create_webserver(iPort);

        Resources ResourceProcessor;
        WebServer.register_resource("/resources/sendform.js", &ResourceProcessor);
        WebServer.register_resource("/resources/loadorderlist.js", &ResourceProcessor);
        WebServer.register_resource("/resources/loaddata.js", &ResourceProcessor);
        WebServer.register_resource("/resources/maincss.css", &ResourceProcessor);

        geology::RequestProcessor PageProcessor;
        WebServer.register_resource("/", &PageProcessor);
        WebServer.register_resource("/authorization", &PageProcessor);
        WebServer.register_resource("/exit", &PageProcessor);
        WebServer.register_resource("/profile", &PageProcessor);
        WebServer.register_resource("/profile/save", &PageProcessor);
        WebServer.register_resource("/order_list", &PageProcessor);
        WebServer.register_resource("/order/[0-9]+", &PageProcessor);
        WebServer.register_resource("/order/[0-9]+/save", &PageProcessor);
        WebServer.register_resource("/order/new", &PageProcessor);
        WebServer.register_resource("/order/new/save", &PageProcessor);

        Res404 NotFound;

        WebServer.register_resource("/[a-zA-Z0-9]+", &NotFound);

        WebServer.start(true);

        return 0;
    }
    catch (std::runtime_error& rExc)
    {
        std::cout << rExc.what() << std::endl;
        return 1;
    }
}
