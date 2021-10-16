#include <iostream>
#include <thread>

#include <httpserver.hpp>

#include "RequestProcessor.h"
#include "IDocFiller.h"

class Resources: public httpserver::http_resource
{
public:
    Resources()
        : m_Reader("E:\\code\\GeologyServer\\resources")
    {
        geology::TemplateReader Reader("E:\\code\\GeologyServer\\resources");
        m_strJsSendForm = Reader.readTemplate("scripts\\SendForm.js");
        m_strJsLoadOrderList = Reader.readTemplate("scripts\\LoadOrderList.js");
        m_strJsProfileData = Reader.readTemplate("scripts\\ProfileScript.js");
        m_strJsManagerData = Reader.readTemplate("scripts\\ManagerDataScript.js");
        m_strJsSpecialistData = Reader.readTemplate("scripts\\SpecialistDataScript.js");
        m_strCssResource = Reader.readTemplate("css\\MainCss.css");
    }

    const std::shared_ptr<httpserver::http_response> render(const httpserver::http_request& crReq)
    {
//        auto strPath = crReq.get_path();
//        if ("/resources/sendform.js" == strPath)
//            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsSendForm));
//        if ("/resources/loadorderlist.js" == strPath)
//            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsLoadOrderList));//specialistdata
//        if ("/resources/profiledata.js" == strPath)
//            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsProfileData));
//        if ("/resources/managerdata.js" == strPath)
//            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsManagerData));
//        if ("/resources/specialistdata.js" == strPath)
//            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strJsManagerData));
//        if ("/resources/maincss.css" == strPath)
//            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_strCssResource, 200, "text/css"));

//        return std::shared_ptr<httpserver::http_response>(new httpserver::http_response(404, "text/plain"));
        auto strPath = crReq.get_path();
        if ("/resources/sendform.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_Reader.readTemplate("scripts\\SendForm.js")));
        if ("/resources/loadorderlist.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_Reader.readTemplate("scripts\\LoadOrderList.js")));//specialistdata
        if ("/resources/profiledata.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_Reader.readTemplate("scripts\\ProfileScript.js")));
        if ("/resources/managerdata.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_Reader.readTemplate("scripts\\ManagerDataScript.js")));
        if ("/resources/specialistdata.js" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_Reader.readTemplate("scripts\\SpecialistDataScript.js")));
        if ("/resources/maincss.css" == strPath)
            return std::shared_ptr<httpserver::http_response>(new httpserver::string_response(m_Reader.readTemplate("css\\MainCss.css"), 200, "text/css"));
        return std::shared_ptr<httpserver::http_response>(new httpserver::http_response(404, "text/plain"));
    }

private:
    geology::TemplateReader m_Reader;

    std::string m_strJsSendForm;
    std::string m_strJsLoadOrderList;
    std::string m_strCssResource;
    std::string m_strJsProfileData;
    std::string m_strJsManagerData;
    std::string m_strJsSpecialistData;


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
        WebServer.register_resource("/resources/profiledata.js", &ResourceProcessor);
        WebServer.register_resource("/resources/managerdata.js", &ResourceProcessor);
        WebServer.register_resource("/resources/specialistdata.js", &ResourceProcessor);
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
        WebServer.register_resource("/document/[0-9]+", &PageProcessor);

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
