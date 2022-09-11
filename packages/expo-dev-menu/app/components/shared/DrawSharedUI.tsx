import * as React from 'react';

import { getComponentData } from './SharedUIRegistry';

function DrawSharedUI(prop) {
  const { componentName } = prop;
  const [componentData, setComponentData] = React.useState(null);

  React.useEffect(() => {
    (async () => {
      const newComponentData = await getComponentData(componentName);
      setComponentData(newComponentData);
    })();
  }, [componentName]);

  if (!componentData) {
    return null;
  }
}

export default DrawSharedUI;
