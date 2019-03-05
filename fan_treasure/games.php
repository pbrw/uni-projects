<?php
include_once 'header.php';
include_once 'navigation.php';
include_once 'helper/accessors.php';
include_once 'helper/printing.php';
include_once 'style.php';



echo "<font size=\"6\"><b>Games</b></font><br><br>";

$games = getAllGames();
printGames($games);


//echo '</div>';
function getAllGames() {
    $roundNumber = getRoundNumber();
    if ($roundNumber == -2) {
        $games = getGamesWhere("true");
    }
    else {
        $games = getGamesWhere("round = " . $roundNumber);
    }

    return $games;
}
