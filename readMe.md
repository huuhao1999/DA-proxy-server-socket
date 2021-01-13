#Proxy-Server-socket
#Mạng máy tính khóa K17

1. Hỗ trợ HTTP 1.0 và HTTP 1.1 
2. Chương trình cho phép Client truy cập website thông qua Proxy Server (GET, POST) 
3. Chương trình chỉ cần hỗ trợ http, không cần https.
4. Proxy Server phải xử lý đồng thời được các request từ client. 
5. Proxy Server sẽ chạy trên port 8888. 
6. Proxy Server cấu hình 1 file blacklist.conf, mỗi dòng chứa các domain website cấm Client truy cập. Proxy Server phải chặn tất cả các truy cập trùng với các domain trong file. 
Ví dụ: abc.com.vn 
           www.thongtin.net ... 
7. Proxy Server có chức năng caching lại những nội dung của trang web, để phục vụ cho Client khác nhanh hơn. Sinh viên tự đưa ra cơ chế caching.
