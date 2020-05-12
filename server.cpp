//
// Created by mershov on 12.05.2020.
//

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::asio::streambuf;


int main() {
    boost::asio::io_service svc;

    tcp::acceptor a(svc);
    a.open(tcp::v4());
    a.set_option(tcp::acceptor::reuse_address(true));
    a.bind({{}, 5000}); // баиндим коннетк по порту 5000
    a.listen(5);

    using session = std::shared_ptr<tcp::socket>;

    std::vector<std::shared_ptr<tcp::socket> > v_s; //в этот массив сложим "клиентов"

    std::function<void()>        do_accept;
    std::function<void(session)> do_session;

    do_session = [&](session s) {
        // начинаем читать
        auto buf = std::make_shared<std::vector<char>>(1024);


        s->async_read_some(boost::asio::buffer(*buf), [&,s,buf](error_code ec, size_t bytes) {
            if (ec) {
                std::cerr << "read failed: " << ec.message() << "\n";
            }
            else {
                std::cout << "Echo to " << s->remote_endpoint(ec) << ": " ;
                std::cout << std::string(buf->data(), bytes) << "end";


                if (ec) {
                    std::cerr << "endpoint failed: " << ec.message() << "\n";
                }
                else {
                    //std::cout << " 11  hello from write";
                    for (auto& s_elem : v_s) {
                        async_write(*s_elem, boost::asio::buffer(*buf), [&, s_elem, buf](error_code ec, size_t) {

                            if (ec) std::cerr << "write failed: " << ec.message() << "\n";

                        });
                    }
                }
                do_session(s); // чтобы не закрывался порт каждый раз после записи

            }

        });
    };


    do_accept = [&] {
        auto s = std::make_shared<session::element_type>(svc);
        a.async_accept(*s, [&,s](error_code ec) {
            if (ec)
                std::cerr << "accept failed: " << ec.message() << "\n";
            else {
                v_s.emplace_back(s);//добавляем к нам в список нового "клиента"
                std::cout << v_s.size();//выводим кол - во элементов в векторе для отладки
                std::cout << std::endl;
                do_session(s);
                do_accept(); // получаем следующий
            }
        });
    };

    do_accept(); // кик
    svc.run();   // ждем закрытия
}