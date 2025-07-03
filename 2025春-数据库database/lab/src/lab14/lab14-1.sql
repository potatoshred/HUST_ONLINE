-- 第一关 从概念模型到MySQL实现

-- 创建数据库
DROP DATABASE IF EXISTS flight_booking;
CREATE DATABASE DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE flight_booking;

-- 用户表
CREATE TABLE user (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    firstname VARCHAR(50) NOT NULL,
    lastname VARCHAR(50) NOT NULL,
    dob DATE NOT NULL,
    sex CHAR(1) NOT NULL,
    email VARCHAR(50),
    phone VARCHAR(30),
    username VARCHAR(20) NOT NULL UNIQUE,
    password CHAR(32) NOT NULL,
    admin_tag TINYINT NOT NULL DEFAULT 0
) ENGINE=InnoDB;

-- 旅客表
CREATE TABLE passenger (
    passenger_id INT AUTO_INCREMENT PRIMARY KEY,
    id CHAR(18) NOT NULL UNIQUE,
    firstname VARCHAR(50) NOT NULL,
    lastname VARCHAR(50) NOT NULL,
    mail VARCHAR(50),
    phone VARCHAR(20) NOT NULL,
    sex CHAR(1) NOT NULL,
    dob DATE
) ENGINE=InnoDB;

-- 机场表
CREATE TABLE airport (
    airport_id INT AUTO_INCREMENT PRIMARY KEY,
    iata CHAR(3) NOT NULL UNIQUE,
    icao CHAR(4) NOT NULL UNIQUE,
    name VARCHAR(50) NOT NULL,
    city VARCHAR(50),
    country VARCHAR(50),
    latitude DECIMAL(11,8),
    longitude DECIMAL(11,8),
    INDEX idx_airport_name (name)
) ENGINE=InnoDB;

-- 航空公司表
CREATE TABLE airline (
    airline_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(30) NOT NULL,
    iata CHAR(2) NOT NULL UNIQUE,
    airport_id INT NOT NULL,
    FOREIGN KEY (airport_id) REFERENCES airport(airport_id),
    INDEX idx_airline_airport_id (airport_id)
) ENGINE=InnoDB;

-- 民航飞机表
CREATE TABLE airplane (
    airplane_id INT AUTO_INCREMENT PRIMARY KEY,
    type VARCHAR(50) NOT NULL,
    capacity SMALLINT NOT NULL,
    identifier VARCHAR(50) NOT NULL,
    airline_id INT NOT NULL,
    FOREIGN KEY (airline_id) REFERENCES airline(airline_id),
    INDEX idx_airplane_airline_id (airline_id)
) ENGINE=InnoDB;

-- 航班常规调度表
CREATE TABLE flightschedule (
    flight_no CHAR(8) PRIMARY KEY,
    airline_id INT NOT NULL,
    departure TIME NOT NULL,
    arrival TIME NOT NULL,
    duration SMALLINT NOT NULL,
    monday TINYINT DEFAULT 0,
    tuesday TINYINT DEFAULT 0,
    wednesday TINYINT DEFAULT 0,
    thursday TINYINT DEFAULT 0,
    friday TINYINT DEFAULT 0,
    saturday TINYINT DEFAULT 0,
    sunday TINYINT DEFAULT 0,
    `from` INT NOT NULL,
    `to` INT NOT NULL,
    FOREIGN KEY (airline_id) REFERENCES airline(airline_id),
    FOREIGN KEY (`from`) REFERENCES airport(airport_id),
    FOREIGN KEY (`to`) REFERENCES airport(airport_id),
    INDEX idx_flightschedule_airline_id (airline_id),
    INDEX idx_flightschedule_from (`from`),
    INDEX idx_flightschedule_to (`to`)
) ENGINE=InnoDB;

-- 航班表
CREATE TABLE flight (
    flight_id INT AUTO_INCREMENT PRIMARY KEY,
    flight_no CHAR(8) NOT NULL,
    airline_id INT NOT NULL,
    airplane_id INT NOT NULL,
    departure DATETIME NOT NULL,
    arrival DATETIME NOT NULL,
    duration SMALLINT NOT NULL,
    `from` INT NOT NULL,
    `to` INT NOT NULL,
    FOREIGN KEY (flight_no) REFERENCES flightschedule(flight_no),
    FOREIGN KEY (airline_id) REFERENCES airline(airline_id),
    FOREIGN KEY (airplane_id) REFERENCES airplane(airplane_id),
    FOREIGN KEY (`from`) REFERENCES airport(airport_id),
    FOREIGN KEY (`to`) REFERENCES airport(airport_id),
    INDEX idx_flight_airline_id (airline_id),
    INDEX idx_flight_airplane_id (airplane_id),
    INDEX idx_flight_flight_no (flight_no),
    INDEX idx_flight_from (`from`),
    INDEX idx_flight_to (`to`)
) ENGINE=InnoDB;

-- 机票表
CREATE TABLE ticket (
    ticket_id INT AUTO_INCREMENT PRIMARY KEY,
    seat CHAR(4),
    price DECIMAL(10,2) NOT NULL,
    flight_id INT NOT NULL,
    passenger_id INT NOT NULL,
    user_id INT NOT NULL,
    FOREIGN KEY (flight_id) REFERENCES flight(flight_id),
    FOREIGN KEY (passenger_id) REFERENCES passenger(passenger_id),
    FOREIGN KEY (user_id) REFERENCES user(user_id),
    INDEX idx_ticket_flight_id (flight_id),
    INDEX idx_ticket_passenger_id (passenger_id),
    INDEX idx_ticket_user_id (user_id)
) ENGINE=InnoDB;

