from Position import Position
import json 

class Position_DAO:
    def __init__(self):
        self.positions = []
        self.occupied = 0
        self.free = 32
        self.reserverd=0

    #Function to create a new parking position
    def new_position(self,id,user,state):
        self.positions.append(Position(id,user,state))
        return True
    
    def set_parking_occupied(self,id,user):
        for position in self.positions:
            if position.id==id:
                position.user=user
                position.state="occupied"
                self.occupied+=1
                self.free-=1
                print("Parqueo "+str(id)+" Ocupado por el usuario: "+str(user))
                return True
    
    def set_parking_free(self,id,user):
        for position in self.positions:
            if position.user==user:
                position.user=None
                if position.state=="occupied":
                    position.state="free"
                    self.occupied-=1
                    self.free+=1
                elif position.state=="reserved":
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
    
    def return_parking_stats(self):
        return {"occupied":self.occupied,
                "reserved":self.reserverd,
                "free":self.free,
                }

    def return_level_one(self):
        return json.dumps([Position.dump() for Position in self.positions if Position.id <=16]) 
    def return_level_two(self):
        return json.dumps([Position.dump() for Position in self.positions if Position.id >=17]) 