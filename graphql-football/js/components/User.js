import React from 'react';
import Relay from 'react-relay';

class User extends React.Component {
  render() {
    const { user } = this.props;
    return (<li>
      { user.name } <em>Age: ({user.age})</em> <b>Friends: {user.friends.map(f => f.name).join(', ')}</b>
      </li>);
  }
}

User.propTypes = {
  user: React.PropTypes.object,
};

User = Relay.createContainer(User, {
  fragments: {
    user: () => Relay.QL`
        fragment on User {
          id
          name
          age
          friends { name }
        }
    `,
  },
});

export default User;
