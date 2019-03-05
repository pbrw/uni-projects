<?php
include_once 'accessors.php';
include_once 'other.php';
include_once 'style.php';

// todo add reversed sorting order
function askSortingOrder($columns) {
    $sortName = getSortName();
    echo "Sort by: <br>";

    $myTeamId = getMyTeamId();
    $myCityId = getMyCityId();
    $file = $_SERVER['PHP_SELF'];
    $action = '"' . $file . '?myTeamId=' . $myTeamId . '&myCityId=' . $myCityId . '"';
    $html = '<form action=' . $action . ' method="post"> <select name="sortName" class="select-style">';

    foreach ($columns as $column) {
        $html .= '<option value=' . $column . ' ';
        if ($column == $sortName) $html .= ' SELECTED';
        $html .= '>' . htmlspecialchars($column) . '</option>';

    }

    $html .= '</select> <input type="submit" class="myButton" value="Select" /><br><br>';

    echo $html;
}

function askForRound($roundsNumber) {
    $roundNumber = getRoundNumber();
    echo "Round: <br>";
    $html = ' <select name="roundNumber" class="select-style">';

    $html .= '<option value=-2 ';
    if ($roundNumber == -2) $html .= "SELECTED";
    $html .= '>All (it may take a while)</option>';

    for($i = 1; $i <= $roundsNumber; $i++) {
        $html .= '<option value=' . $i . ' ';
        if ($i == $roundNumber) $html .= ' SELECTED';
        $html .= '>' . htmlspecialchars($i) . '</option>';

    }

    $html .= '</select> <input type="submit" class="myButton" value="Select" /> </form>';

    echo $html;
}

function askForTeam() {
    $selectedTeam = getSelectedTeam();
    echo "Select team: ";

    $myTeamId = getMyTeamId();
    $myCityId = getMyCityId();
    $action = '"/teams.php?myTeamId=' . $myTeamId . '&myCityId=' . $myCityId . '"';
    $html = '<form action=' . $action . '  method="post"> <select name="selectedTeam" class="select-style">';

    $teams = getTeams();

    foreach ($teams as $key => $value) {
        $html .= '<option value=' . $value['team_id'];
        if ($selectedTeam == $value['team_id']) $html .= ' SELECTED';
        $html .= '>'. htmlspecialchars($value['name']) . '</option>';
    }

    $html .= '</select> <input type="submit" class="myButton" value="Select" />';

    echo $html;
}

function printGames(&$games) {
    $columns = ['round',
        'host',
        'guest',
        'date',
        'score1',
        'score2'];

    $games = addAttraction($games);
    array_push($columns, 'attraction');

    if (getMyCityId() != -1) {
        addDistance($games);
        array_push($columns, 'distance');
    }
    askSortingOrder($columns);
    $roundsNumber =  2 * getTeamsNumber() - 2;
    askForRound($roundsNumber);
    $myTeamId = getMyTeamId();
    $sortName = getSortName();

    sortTable($games, $sortName);

    $html = '<table class="blueTable" align="center">';
    $html .= '<tr>';

    foreach ($columns as $column) {
        $html .= '<th>' . htmlspecialchars($column) . '</th>';
    }
    $html .= '</tr>';

    foreach ($games as $key=>$row) {
        $html .= '<tr';
        if ($row['host_id'] == $myTeamId || $row['guest_id'] == $myTeamId) {
            $html .= ' bgcolor="#FFFF00"';
        }
        else if ($key % 2 == 0) {
            $html .= ' bgcolor="#D0E4F5"';
        }
        $html .= '>';
        foreach ($columns as $column) {
            $html .= '<td>' . htmlspecialchars($row[$column]) . '</td>';
        }
        $html .= '</tr>';
    }
    $html .= '</table>';

    echo $html;
}