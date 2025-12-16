-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 16, 2025 at 05:01 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_robot`
--

-- --------------------------------------------------------

--
-- Table structure for table `status_robot`
--

CREATE TABLE `status_robot` (
  `id` int(11) NOT NULL DEFAULT 1,
  `modeOperasi` varchar(50) DEFAULT NULL,
  `arahApi` varchar(50) DEFAULT NULL,
  `pompaStatus` varchar(10) DEFAULT NULL,
  `baseAngle` int(11) DEFAULT NULL,
  `shoulderAngle` int(11) DEFAULT NULL,
  `elbowAngle` int(11) DEFAULT NULL,
  `wristAngle` int(11) DEFAULT NULL,
  `sensorKiri` int(11) DEFAULT NULL,
  `sensorKanan` int(11) DEFAULT NULL,
  `sensorTengahAnalog` int(11) DEFAULT NULL,
  `last_update` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `status_robot`
--

INSERT INTO `status_robot` (`id`, `modeOperasi`, `arahApi`, `pompaStatus`, `baseAngle`, `shoulderAngle`, `elbowAngle`, `wristAngle`, `sensorKiri`, `sensorKanan`, `sensorTengahAnalog`, `last_update`) VALUES
(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '2025-11-28 02:51:08');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `status_robot`
--
ALTER TABLE `status_robot`
  ADD PRIMARY KEY (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
