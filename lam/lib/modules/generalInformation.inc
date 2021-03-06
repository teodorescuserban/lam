<?php
/*

  This code is part of LDAP Account Manager (http://www.ldap-account-manager.org/)
  Copyright (C) 2011 - 2019  Roland Gruber

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
* Shows general information like the creation time of an account.
*
* @package modules
* @author Roland Gruber
*/

/**
* Shows general information like the creation time of an account.
*
* @package modules
*/
class generalInformation extends baseModule {

	/**
	* Returns true if this module can manage accounts of the current type, otherwise false.
	*
	* @return boolean true if module fits
	*/
	public function can_manage() {
		return in_array($this->get_scope(), LAM\TYPES\getTypes());
	}

	/**
	* Returns meta data that is interpreted by parent class
	*
	* @return array array with meta data
	*
	* @see baseModule::get_metaData()
	*/
	public function get_metaData() {
		$return = array();
		// icon
		$return['icon'] = 'info.png';
		// alias name
		$return["alias"] = _("General information");
		// module dependencies
		$return['dependencies'] = array('depends' => array(), 'conflicts' => array());
		// managed attributes
		$return['attributes'] = array('creatorsName', 'createTimestamp', 'modifiersName',
			'modifyTimestamp', 'hasSubordinates', 'memberOf');
		$return['hiddenAttributes'] = array('creatorsName', 'createTimestamp', 'modifiersName',
			'modifyTimestamp', 'hasSubordinates');
		return $return;
	}

	/**
	 * Returns the HTML meta data for the main account page.
	 *
	 * @return htmlElement HTML meta data
	 */
	public function display_html_attributes() {
		$return = new htmlResponsiveRow();
		// creation info
		if (isset($this->attributes['creatorsName'][0])) {
			$return->addLabel(new htmlOutputText(_('Created by')));
			$return->addField(new htmlOutputText(getAbstractDN($this->attributes['creatorsName'][0])));
		}
		if (isset($this->attributes['createTimestamp'][0])) {
			$return->addLabel(new htmlOutputText(_('Creation time')));
			$return->addField(new htmlOutputText(formatLDAPTimestamp($this->attributes['createTimestamp'][0])));
		}
		if (isset($this->attributes['creatorsName'][0]) || isset($this->attributes['createTimestamp'][0])) {
			$return->addVerticalSpacer('1rem');
		}
		// modification info
		if (isset($this->attributes['modifiersName'][0])) {
			$return->addLabel(new htmlOutputText(_('Modified by')));
			$return->addField(new htmlOutputText(getAbstractDN($this->attributes['modifiersName'][0])));
		}
		if (isset($this->attributes['modifyTimestamp'][0])) {
			$return->addLabel(new htmlOutputText(_('Modification time')));
			$return->addField(new htmlOutputText(formatLDAPTimestamp($this->attributes['modifyTimestamp'][0])));
		}
		if (isset($this->attributes['modifiersName'][0]) || isset($this->attributes['modifyTimestamp'][0])) {
			$return->addVerticalSpacer('1rem');
		}
		// children
		if (isset($this->attributes['hasSubordinates'][0])) {
			$hasChilds = _('no');
			if ($this->attributes['hasSubordinates'][0] == 'TRUE') {
				$hasChilds = _('yes');
			}
			$return->addLabel(new htmlOutputText(_('Has subentries')));
			$return->addField(new htmlOutputText($hasChilds));
			$return->addVerticalSpacer('1rem');
		}
		// group memberships
		if (isset($this->attributes['memberOf'][0])) {
			$groupLabel = new htmlOutputText(_('Groups'));
			$groupLabel->alignment = htmlElement::ALIGN_TOP;
			$return->addLabel($groupLabel);
			$groups = new htmlTable();
			for ($i = 0; $i < sizeof($this->attributes['memberOf']); $i++) {
				$groups->addElement(new htmlOutputText(getAbstractDN($this->attributes['memberOf'][$i])), true);
			}
			$return->addField($groups);
		}
		return $return;
	}

	/**
	* Processes user input of the primary module page.
	* It checks if all input values are correct and updates the associated LDAP attributes.
	*
	* @return array list of info/error messages
	*/
	public function process_attributes() {
		return array();
	}

}


?>
