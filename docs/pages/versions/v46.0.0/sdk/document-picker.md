---
title: DocumentPicker
sourceCodeUrl: 'https://github.com/expo/expo/tree/sdk-46/packages/expo-document-picker'
packageName: 'expo-document-picker'
---

import APISection from '~/components/plugins/APISection';
import {APIInstallSection} from '~/components/plugins/InstallSection';
import PlatformsSection from '~/components/plugins/PlatformsSection';
import Video from '~/components/plugins/Video'

Provides access to the system's UI for selecting documents from the available providers on the user's device.

<Video file={"sdk/documentpicker.mp4"} loop={false} />

<PlatformsSection android emulator ios simulator web />

## Installation

<APIInstallSection />

## Configuration

### Managed workflow

For iOS, outside of the Expo Go app, the DocumentPicker module requires the [iCloud Services Entitlement](https://developer.apple.com/documentation/bundleresources/entitlements/com_apple_developer_icloud-services) to work properly. You need to take the following steps:

- Set the `usesIcloudStorage` key to `true` in your **app.json** as specified [configuration properties](/versions/latest/config/app/#usesicloudstorage).
- You need to enable the iCloud Application Service in your App identifier. This can be done in the detail of your [App ID in the Apple Developer interface](https://developer.apple.com/account/resources/identifiers/list).
- Enable iCloud service with CloudKit support, and create an iCloud Container. When registering the new Container, you are asked to provide a description and identifier for the container. You may enter any name under the description. Under the identifier, add `iCloud.<your_bundle_identifier>`.

To apply these changes, you have to revoke your existing provisioning profile and use [EAS Build](/build/introduction/) to build the app binaries.

### Bare workflow

For iOS bare projects, the `DocumentPicker` module requires the iCloud entitlement to work properly. If your app doesn't have it already, you can add it by opening the project in Xcode and following these steps:

- In the project, go to the `Capabilities` tab
- Set the iCloud switch to `on`
- Check the `iCloud Documents` checkbox

## API

```js
import * as DocumentPicker from 'expo-document-picker';
```

<APISection packageName="expo-document-picker" apiName="DocumentPicker" />
