<?php
include_once 'header.php';
include_once 'navigation.php';
include_once 'helper/printing.php';
include_once 'helper/accessors.php';
include_once 'style.php';

echo "<font size=\"6\"><b>Teams</b></font><br><br>";

$selectedTeam = getSelectedTeam();

askForTeam();
printTeamInfo($selectedTeam);

if ($selectedTeam != -1) {
    $games = getGamesOf($selectedTeam);
    printGames($games);
}

function getGamesOf($team) {
    $roundNumber = getRoundNumber();
    if ($roundNumber != -2) {
        return getGamesWhere("round = " . $roundNumber . " and (host_id = " . $team . " or " . "guest_id = " . $team . ")");
    }
    else {
        return getGamesWhere(" (host_id = " . $team . " or " . "guest_id = " . $team . ")");
    }

}

function printTeamInfo($team) {
    $teamRow = getTeamRow($team);

    $columns = ['name',
                'city',
                'league',
                'points',
                'wins',
                'loses',
                'draws',
                'goals_for',
                'goals_against',
                'diff'];

    $html = '<table class="blueTable" align="center">';

    foreach ($columns as $column) {
        $html .= '<tr>';
        $html .= '<th>' . htmlspecialchars($column) . '</th>';
        $html .= '<td>' . htmlspecialchars($teamRow[0][$column]) . '</td>';
        $html .= '</tr>';
    }

    $html .= '</table><br>';

    echo $html;

}