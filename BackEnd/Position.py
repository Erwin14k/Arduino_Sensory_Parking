class Position:
    def __init__(self,id,user,state):
        self.id = id 
        self.user = user
        self.state = state

    def dump(self):
        return {
            self.id: self.state,
        }