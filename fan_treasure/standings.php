<?php
include_once 'header.php';
include_once 'navigation.php';
include_once 'helper/accessors.php';
include_once 'helper/database.php';
include_once 'helper/printing.php';
include_once 'helper/other.php';
include_once 'style.php';

echo "<font size=\"6\"><b>Standings</b></font><br><br>";

$standings = getStandings();
$columns = ['position',
            'name',
            'points',
            'wins',
            'loses',
            'draws',
            'goals_for',
            'goals_against',
            'diff'];

askSortingOrder($columns);
printStandings($standings, $columns);
function getStandings() {
    $columns = ['t.team_id',
                'p.position',
                't.name',
                't.points',
                't.wins',
                't.loses',
                't.draws',
                't.goals_for',
                't.goals_against',
                't.goals_for - t.goals_against as diff'];

    $tableName = 'Positions as p JOIN Teams as t ON p.team_id = t.team_id ORDER BY p.position';
    $standings = getTable($tableName, $columns);

    return $standings;
}

function printStandings($standings, $columns) {
    sortTable($standings, getSortName());

    $myTeamId = getMyTeamId();

    $html = '<table class="blueTable" align="center">';
    $html .= '<tr>';

    foreach ($columns as $column) {
        $html .= '<th>' . htmlspecialchars($column) . '</th>';
    }
    $html .= '</tr>';

    $i = 0;
    foreach ($standings as $key=>$row) {
        $html .= '<tr';
        if ($row['team_id'] == $myTeamId) {
            $html .= ' bgcolor="#FFFF00"';
        }
        else if ($i % 2 == 0) {
            $html .= ' bgcolor="#D0E4F5"';
        }
        $html .= '>';
        foreach ($columns as $column) {
            $html .= '<td>' . htmlspecialchars($row[$column]) . '</td>';
        }
        $html .= '</tr>';
        $i++;
    }
    $html .= '</table>';

    echo $html;
}