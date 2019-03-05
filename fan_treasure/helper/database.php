<?php

function connect() {
    $servername = "localhost";
    $username = "29673544_database";
    $password = "Kryniowese8128";

    try {
        $conn = new PDO("mysql:host=$servername;dbname=" . $username, $username, $password,
            [PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8', PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    } catch (PDOException $e) {
        echo "Connection failed: " . $e->getMessage();
    }

    return $conn;
}

function queryDatabase($conn, $query) {
    $sth = $conn->prepare($query);
    $sth->execute();
    $arr = $sth->fetchAll();
    return $arr;
}

function voidQueryDatabase($conn, $query) {
    $sth = $conn->prepare($query);
    $sth->execute();
}

function getTable($name, $columns) {
    $conn = connect();

    $query = 'SELECT ';
    $i = 0;
    foreach ($columns as $column) {
        if ($i > 0) $query .= ', ';
        $query .= $column . ' ';
        $i++;
    }

    $query .= 'FROM ';
    $query .= $name.';';

//    echo $query;
    return queryDatabase($conn, $query);
}

function getFullTable($name) {
    return getTable($name, ['*']);
}