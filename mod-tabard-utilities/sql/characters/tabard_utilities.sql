-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.7.33-log - MySQL Community Server (GPL)
-- Server OS:                    Win64
-- HeidiSQL Version:             11.3.0.6295
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Dumping database structure for _acore_characters
CREATE DATABASE IF NOT EXISTS `_acore_characters` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;
USE `_acore_characters`;

-- Dumping structure for table _acore_characters.tabard_utilities
CREATE TABLE IF NOT EXISTS `tabard_utilities` (
  `TEntry` int(11) NOT NULL,
  `Function` int(11) NOT NULL,
  `Requirements` int(11) NOT NULL DEFAULT '0',
  `ZoneID` int(11) NOT NULL DEFAULT '0',
  `EnemyFactionID` int(11) NOT NULL DEFAULT '0',
  `CreatureEntry` int(11) NOT NULL DEFAULT '0',
  `FactionID` int(11) NOT NULL DEFAULT '0',
  `Value` int(11) NOT NULL DEFAULT '0',
  `Count` int(11) NOT NULL DEFAULT '1',
  `Comment` varchar(100) NOT NULL DEFAULT 'Description',
  PRIMARY KEY (`TEntry`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Dumping data for table _acore_characters.tabard_utilities: ~3 rows (approximately)
DELETE FROM `tabard_utilities`;
/*!40000 ALTER TABLE `tabard_utilities` DISABLE KEYS */;
INSERT INTO `tabard_utilities` (`TEntry`, `Function`, `Requirements`, `ZoneID`, `EnemyFactionID`, `CreatureEntry`, `FactionID`, `Value`, `Count`, `Comment`) VALUES
	(7725, 0, 2, 1581, 0, 0, 76, 50, 0, 'Example: Gives 50 points of rep with Orgrimmar when killing DM\'s creature'),
	(23709, 1, 0, 0, 0, 0, 0, 1, 0, 'Example: Gives 1 Gold when killing any creature'),
	(35279, 2, 3, 0, 0, 80, 0, 47241, 2, 'Example: Gives 2 Emblems of Triumph when killing a specific creature');
/*!40000 ALTER TABLE `tabard_utilities` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
