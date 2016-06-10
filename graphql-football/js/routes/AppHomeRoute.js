import Relay from 'react-relay';

export default class extends Relay.Route {
  static queries = {
    store: (Component) => Relay.QL`
      query TeaStoreQuery {
        store { ${Component.getFragment('store')} },
      }
    `,
  };
  static routeName = 'AppHomeRoute';
}
