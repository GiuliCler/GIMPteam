-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Creato il: May 01, 2020 alle 11:55
-- Versione del server: 10.1.40-MariaDB
-- Versione PHP: 7.3.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `gimpdocs_db`
--
CREATE DATABASE IF NOT EXISTS `gimpdocs_db` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `gimpdocs_db`;

-- --------------------------------------------------------

--
-- Struttura della tabella `doc`
--

DROP TABLE IF EXISTS `doc`;
CREATE TABLE `doc` (
  `nome_doc` varchar(40) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `uri` varchar(50) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `doc`
--

INSERT INTO `doc` (`nome_doc`, `uri`) VALUES
('DivinaCommedia', '://GIMPdocs/80423b4c7a9c3e047148ececb88d1d41'),
('Oibaboi', '://GIMPdocs/3b32d34c78a03e759aa185702748c408');

-- --------------------------------------------------------

--
-- Struttura della tabella `utente_doc`
--

DROP TABLE IF EXISTS `utente_doc`;
CREATE TABLE `utente_doc` (
  `username` varchar(50) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `nome_doc` varchar(40) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `site_id` int(1) NOT NULL,
  `site_counter` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `utente_doc`
--

INSERT INTO `utente_doc` (`username`, `nome_doc`, `site_id`, `site_counter`) VALUES
('ilagioda@gimpteam.it', 'DivinaCommedia', 0, 0),
('ilagioda@gimpteam.it', 'Oibaboi', 0, 0);

-- --------------------------------------------------------

--
-- Struttura della tabella `utenti`
--

DROP TABLE IF EXISTS `utenti`;
CREATE TABLE `utenti` (
  `username` varchar(50) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `password` varchar(260) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `sale` varchar(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `nickname` varchar(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `icona` varchar(40) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `utenti`
--

INSERT INTO `utenti` (`username`, `password`, `sale`, `nickname`, `icona`) VALUES
('ilagioda@gimpteam.it', 'mZ�����41�{��>���o�����~����', 'frAQBc8Wsa', 'ilagio', 'Manaphy.png');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `doc`
--
ALTER TABLE `doc`
  ADD PRIMARY KEY (`nome_doc`);

--
-- Indici per le tabelle `utente_doc`
--
ALTER TABLE `utente_doc`
  ADD PRIMARY KEY (`username`,`nome_doc`);

--
-- Indici per le tabelle `utenti`
--
ALTER TABLE `utenti`
  ADD PRIMARY KEY (`username`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
