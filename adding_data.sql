use esb_db;
INSERT INTO routes(sender,destination,message_type,is_active)
VALUES ("rockyrohan890@gmail.com","rockyrohan890@gmail.com","xml",1),
("rockyrohan890@gmail.com","sohan.jumanal@gmail.com","json",1),
("rockyrohan890@gmail.com","sohan.jumanal@gmail.com","xml",1);

INSERT INTO transport_config(route_id,config_key,config_value)
VALUES (1,"url","https://ifsc.razorpay.com/"),
(2,"mail","rockyrohan890@gmail.com"),
(3,"mail","sohan.jumanal@gmail.com");

INSERT INTO transform_config(route_id,config_key,config_value)
VALUES (1,"IFSC","xml"),
(2,"IFSC","json"),
(3,"IFSC","json");
