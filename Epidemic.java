import java.util.*;

// klasa odpowiedzialna za koordynacje symulacji 

public class Epidemic {
    public static Random rand;
    
    private Props props;
    private Agent[] agents;
    private ArrayList<LinkedList<Meeting>> meetings;
    
    public static int healthy, infected, resistant;
    
    // generuje zadaną liczbę agentów    
    private void genAgents(int agentsNumber) {
        agents = new Agent[agentsNumber];
        
        for (int i = 0; i < agentsNumber; i++) {
            agents[i] = new Agent(i + 1, props.probSociable, props.probMeeting);
        }
        
        agents[rand.nextInt(agentsNumber)].infect();
    }
    
    // generuje krawędź
    private void genEdge() {
        int x, y;
        do {
            x = rand.nextInt(props.agentsNumber);
            y = rand.nextInt(props.agentsNumber);
        }
        while (x == y || agents[x].friend(agents[y]));
        
        agents[x].addFriend(agents[y]);
        agents[y].addFriend(agents[x]);
    }
    
    // generuje zadaną liczbę krawędzi
    private void genEdges(int edgesNumber) {
        for (int i = 0; i < edgesNumber; i++) {
            genEdge();
        }
    }
    
    public Epidemic(Props props) {
        this.healthy = props.agentsNumber;
        this.infected = 0;
        this.resistant = 0;    
    
        this.props = props;
        rand = new Random(this.props.seed);
        meetings = new ArrayList<>();
        for (int i = 0; i <= props.daysNumber; i++) {
            meetings.add(new LinkedList<Meeting>());
        }
        
        genAgents(this.props.agentsNumber);
        genEdges(this.props.avgFriends * this.props.agentsNumber / 2);
    } 
    
    // sprawdza zainferkowane osoby
    private void checkInfected() {
        for (Agent agent : agents) {
            if (!agent.alive()) continue;
            
            if (agent.infected()) {
                if (rand.nextDouble() <= props.mortality) 
                    agent.kill();
                else if (rand.nextDouble() <= props.probHealing) 
                    agent.heal();
            }
        }
    }
    
    // generuje spotkania danego dnia
    private void genMeetings(int day) {
        int newDay, newAgent;
        for (Agent agent : agents) {
            if (!agent.alive()) continue;
            
            while (rand.nextDouble() <= agent.probMeeting) {  
                Agent[] friends;              
                
                if (agent.sociable() && !agent.infected())
                    friends = agent.getMoreFriends();
                else
                    friends = agent.getFriends();
                    
                if (friends.length == 0) continue;
                
                newDay = rand.nextInt(props.daysNumber - day) + day + 1;
                newAgent = rand.nextInt(friends.length);
                meetings.get(newDay).add(new Meeting(agent, friends[newAgent]));
            }
        }
    }
    
    // sprawdza wynik spotkań danego dnia
    private void checkMeetings(int day) {
        for (Meeting meeting : meetings.get(day)) {
            if (!meeting.first.alive()) continue;
            if (!meeting.second.alive()) continue;
            
            meeting.sort();
            if (meeting.first.infected() && meeting.second.healthy()) {
                if (rand.nextDouble() <= props.probInfection) {
                    meeting.second.infect();
                }
            }
        }
    }
    
    // symuluje kolejne dni
    public void simulate() {
        for (int day = 1; day <= props.daysNumber; day++) {
            checkInfected();
            if (day != props.daysNumber) genMeetings(day);
            checkMeetings(day);
            System.out.println(healthy + " " + infected + " " + resistant);
        }
    }
    
    // drukuje raport
    public void report() {
        System.out.println("# twoje wyniki powinny zawierać te komentarze\n");
        System.out.println("# Parametry wejściowe:");
        System.out.println("seed = " + props.seed);
        System.out.println("liczbaAgentów = " + props.agentsNumber);
        System.out.println("prawdTowarzyski = " + props.probSociable);
        System.out.println("prawdSpotkania = " + props.probMeeting);
        System.out.println("prawdZarażenia = " + props.probInfection);
        System.out.println("prawdWyzdrowienia = " + props.probHealing);
        System.out.println("śmiertelność = " + props.mortality);
        System.out.println("liczbaDni = " + props.daysNumber);
        System.out.println("śrZnajomych = " + props.avgFriends);
        
        System.out.println("");
        System.out.println("# Agenci jako: id typ lub id* typ dla chorego");
        for (int i = 0; i < props.agentsNumber; i++) {
            System.out.println(agents[i]); 
        }
        
        System.out.println("");
        System.out.println("# Graf");    
        
        for (int i = 0; i < props.agentsNumber; i++) {
            System.out.print(i + 1 + " ");
            agents[i].printFriends();
            System.out.println();
        }
        
        System.out.println("");
        System.out.println("# Liczność w kolejnych dniach");
        System.out.println(healthy + " " + infected + " " + resistant);
    }   
    
}
