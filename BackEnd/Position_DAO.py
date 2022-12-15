from Position import Position
import json 

class Position_DAO:
    def __init__(self):
        self.positions = []
        self.occupied = 0
        self.free = 32
        self.reserverd=0

    #Function to create a new parking position
    def new_position(self,id,user,state,alarm,attack):
        self.positions.append(Position(id,user,state,alarm,attack))
        return True
    
    def set_parking_free_by_reserved(self,id,user):
        for position in self.positions:
            if position.user==user:
                position.user=-1
                position.state="free"
                self.reserverd-=1
                self.free+=1
                print("Parqueo Reservado por el usuario "+str(user)+" Libre nuevamente. ")
                return True
    
    def set_parking_reserved(self,id,user):
        for position in self.positions:
            if position.id==id:
                if position.state=="free":
                    position.user=user
                    position.state="reserved"
                    self.reserverd+=1
                    self.free-=1
                    print("Parqueo "+str(id)+" reservado por el usuario: "+str(user))
                    return True
                else:
                    return False
    
    def set_parking_occupied(self,id,user):
        for position in self.positions:
            if position.id==id:
                position.user=user
                self.occupied+=1
                self.free-=1
                print("Parqueo "+str(id)+" ocupado por el usuario: "+str(user))
                return True

    def set_parking_occupied_by_reserved(self,id,user):
        for position in self.positions:
            if position.user==user:
                if position.state=="reserved" and position.user==user:
                    position.state="occupied"
                    self.occupied+=1
                    self.reserverd-=1
                    print("Parqueo reservado "+str(position.id)+" ocupado por el usuario: "+str(user))
                    return True
                else:
                    return False
    
    def return_parking_stats(self):
        return {"occupied":self.occupied,
                "reserved":self.reserverd,
                "free":self.free,
                }
    def return_alarm_analytics(self,user):
        for position in self.positions:
            if position.user==user:
                return {"parking":position.id,
                    "alarm":position.alarm,
                    "attack":position.attack,
                    }
        return{
            "error":"true",
        }
    
    def turn_off_the_alarm(self,user):
        for position in self.positions:
            if position.user==user:
                position.alarm="off"
                return True
    
    def turn_on_the_alarm(self,user):
        for position in self.positions:
            if position.user==user:
                position.alarm="on"
                return True

    def return_level_one(self):
        return json.dumps([Position.dump() for Position in self.positions if Position.id <=16]) 
    def return_level_two(self):
        return json.dumps([Position.dump() for Position in self.positions if Position.id >=17]) 