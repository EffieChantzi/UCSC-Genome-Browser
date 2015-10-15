var pt=React.PropTypes;var CheckboxLabel=React.createClass({displayName:"CheckboxLabel",mixins:[PathUpdate,ImmutableUpdate],propTypes:{checked:pt.bool,label:pt.string,className:pt.string,style:pt.object},getDefaultProps:function(){return{checked:false,label:""}},handleClick:function(e){var newVal=e.target.checked;this.props.update(this.props.path,newVal)},render:function(){return React.createElement("div",{key:this.props.ref,className:this.props.className,style:this.props.style},React.createElement("input",{type:"checkbox",checked:this.props.checked,onChange:this.handleClick}),this.props.label)}});CheckboxLabel=CheckboxLabel;var pt=React.PropTypes;var CladeOrgDb=React.createClass({displayName:"CladeOrgDb",mixins:[PathUpdate,ImmutableUpdate],propTypes:{menuData:pt.object.isRequired},render:function(){var menuData=this.props.menuData;var path=this.props.path||[];return React.createElement("div",null,React.createElement(LabeledSelect,{label:"group",selected:menuData.get("clade"),className:"sectionItem",options:menuData.get("cladeOptions"),update:this.props.update,path:path.concat("clade")}),React.createElement(LabeledSelect,{label:"genome",selected:menuData.get("org"),className:"sectionItem",options:menuData.get("orgOptions"),update:this.props.update,path:path.concat("org")}),React.createElement(LabeledSelect,{label:"assembly",selected:menuData.get("db"),className:"sectionItem",options:menuData.get("dbOptions"),update:this.props.update,path:path.concat("db")}))}});CladeOrgDb=CladeOrgDb;var pt=React.PropTypes;var Icon=React.createClass({displayName:"Icon",mixins:[PathUpdateOptional,ImmutableUpdate],propTypes:{type:pt.oneOf(["plus","spinner","times","remove","x","arrows-v","upDown"]).isRequired,className:pt.string},onClick:function(){if(this.props.update){this.props.update(this.props.path)}},render:function(){var faClass="fa ";switch(this.props.type){case"plus":faClass+="fa-plus";break;case"spinner":faClass+="fa-spinner fa-spin";break;case"times":case"remove":case"x":faClass+="fa-times";break;case"arrows-v":case"upDown":faClass+="fa-arrows-v";break;default:console.warn('Icon: Unrecognized type "'+this.props.type+'"')}faClass+=" iconButton";if(this.props.className){faClass+=" "+this.props.className}return React.createElement("i",{className:faClass,onClick:this.onClick})}});Icon=Icon;var pt=React.PropTypes;var LabeledSelect=React.createClass({displayName:"LabeledSelect",mixins:[PathUpdate,ImmutableUpdate],propTypes:{label:pt.string.isRequired,selected:pt.string,options:pt.object,className:pt.string},optionFromValueLabel:function(item){var value=item.get("value"),label=item.get("label"),disabled=item.get("disabled");return React.createElement("option",{value:value,key:value,disabled:disabled},label)},onChange:function(e){var newValue=e.target.value;this.props.update(this.props.path,newValue)},render:function(){var opts=null;if(this.props.options){opts=this.props.options.map(this.optionFromValueLabel).toJS()}return React.createElement("div",{className:this.props.className},React.createElement("div",null,this.props.label),React.createElement("select",{className:"groupMenu",value:this.props.selected,onChange:this.onChange},opts))}});LabeledSelect=LabeledSelect;var pt=React.PropTypes;var LoadingImage=React.createClass({displayName:"LoadingImage",propTypes:{loading:pt.bool.isRequired,message:pt.string},getDefaultProps:function(){return{message:"Executing your query may take some time.  "+"Please leave this window open during processing."}},render:function(){if(this.props.loading){return React.createElement("div",null,React.createElement("img",{id:"loadingImg",src:"../images/loading.gif"}),React.createElement("p",{className:"loadingMessage"},this.props.message))}else{return null}}});LoadingImage=LoadingImage;var pt=React.PropTypes;function getScrollHeight(){var supportPageOffset=window.pageXOffset!==undefined;var isCSS1Compat=(document.compatMode||"")==="CSS1Compat";return supportPageOffset?window.pageYOffset:isCSS1Compat?document.documentElement.scrollTop:document.body.scrollTop}var Modal=React.createClass({displayName:"Modal",mixins:[PathUpdate],propTypes:{title:pt.renderable.isRequired},componentWillUnmount:function(){window.scrollTo(0,this.origY)},render:function(){var path=this.props.path||[];var title=React.createElement("div",null,React.createElement("span",{className:"floatLeft"},this.props.title),React.createElement(Icon,{type:"remove",className:"removeButton floatRight",path:path.concat("remove"),update:this.props.update}),React.createElement("div",{className:"clear"}));if(!this.top){this.origY=getScrollHeight();this.top=this.origY+75}return React.createElement("div",{style:{top:this.top},className:"absoluteModal"},React.createElement(Section,{style:{margin:0},title:title},this.props.children))}});Modal=Modal;var pt=React.PropTypes;var PositionPopup=null;var PositionSearch=React.createClass({displayName:"PositionSearch",mixins:[PathUpdate,ImmutableUpdate],propTypes:{positionInfo:pt.object.isRequired,db:pt.string,className:pt.string},autoCompleteSourceFactory:function(db){var baseUrl="../cgi-bin/hgSuggest?db="+db+"&prefix=";var cache={};return function(request,acCallback){var key=request.term;if(cache[key]){acCallback(cache[key])}else{var url=baseUrl+encodeURIComponent(key);$.getJSON(url).done(function(result){cache[key]=result;acCallback(result)})}}},autoCompleteMenuOpen:function(){var $jq=$(this.refs.input.getDOMNode());var pos=$jq.offset().top+$jq.height();if(!isNaN(pos)){var maxHeight=$(window).height()-pos-30;var auto=$(".ui-autocomplete");var curHeight=$(auto).children().length*21;if(curHeight>maxHeight){$(auto).css({maxHeight:maxHeight+"px",overflow:"scroll",zIndex:12})}else{$(auto).css({maxHeight:"none",overflow:"hidden",zIndex:12})}}},autoCompleteSelectFactory:function(geneTrack){return function(event,ui){this.setState({position:ui.item.id,hgFindParams:{track:geneTrack,vis:"pack",extraSel:"",matches:ui.item.internalId}});this.props.update(this.props.path.concat("position"),ui.item.id);event.preventDefault()}.bind(this)},componentDidMount:function(){var inputNode,$input;var geneSuggestTrack=this.props.positionInfo.get("geneSuggestTrack");if(geneSuggestTrack){inputNode=this.refs.input.getDOMNode();$input=$(inputNode);$input.autocomplete({delay:500,minLength:2,source:this.autoCompleteSourceFactory(this.props.db),open:this.autoCompleteMenuOpen,select:this.autoCompleteSelectFactory(geneSuggestTrack)});if(inputNode.onbeforedeactivate!==undefined){console.log("IE8 onbeforedeactivate hack");$input.on("beforedeactivate",function(ev){if(ev.originalEvent&&ev.originalEvent.toElement&&/ui-state-focus/.test(ev.originalEvent.toElement.className)){ev.preventDefault()}})}}},render:function(){var posInfo=this.props.positionInfo;var spinner=null,posPopup=null;var loading=posInfo.get("loading");if(loading){spinner=React.createElement(Icon,{type:"spinner",className:"floatRight"})}var matches=posInfo.get("positionMatches");if(matches){posPopup=React.createElement(PositionPopup,{positionMatches:matches,update:this.props.update,path:this.props.path})}if(loading||matches){$(this.refs.input.getDOMNode()).blur()}return React.createElement("div",{className:this.props.className},React.createElement(TextInput,{value:posInfo.get("position"),path:this.props.path.concat("position"),update:this.props.update,size:45,ref:"input"}),spinner,posPopup)}});PositionPopup=React.createClass({displayName:"PositionPopup",mixins:[PathUpdate,ImmutableUpdate],propTypes:{positionMatches:pt.object.isRequired},makePosMatchLink:function(matches,i){var position=matches.get("position");var description=matches.get("description");description=description?" - "+description:null;var posName=matches.get("posName");var posLabel=posName;if(position){var update=this.props.update;var path=this.props.path.concat("positionMatch");var onClick=function(e){update(path,matches);e.preventDefault();e.stopPropagation()};posLabel=React.createElement("span",null,React.createElement("a",{href:"#",onClick:onClick,className:"posLink"},posName)," at "+position)}return React.createElement("div",{key:i},posLabel," ",description)},makePosPopupSection:function(trackMatches,i){return React.createElement("div",{key:i},React.createElement("h3",null,trackMatches.get("description")),trackMatches.get("matches").map(this.makePosMatchLink).toJS(),React.createElement("br",null))},render:function(){return React.createElement(Modal,{title:"Your search turned up multiple results; please choose one.",path:this.props.path.concat("hidePosPopup"),update:this.props.update},this.props.positionMatches.map(this.makePosPopupSection).toJS())}});PositionSearch=PositionSearch;var pt=React.PropTypes;var Section=React.createClass({displayName:"Section",propTypes:{title:pt.node.isRequired,style:pt.object},render:function(){return React.createElement("div",{className:"sectionBorder sectionPanel",style:this.props.style},React.createElement("div",{className:"sectionHeader"},this.props.title),React.createElement("div",{className:"sectionContents"},this.props.children))}});Section=Section;var SetClearButtons=React.createClass({displayName:"SetClearButtons",mixins:[PathUpdate,ImmutableUpdate],onSetAll:function(){this.props.update(this.props.path,true)},onClearAll:function(){this.props.update(this.props.path,false)},render:function(){return React.createElement("div",null,React.createElement("input",{type:"button",value:"Set all",onClick:this.onSetAll}),React.createElement("input",{type:"button",value:"Clear all",onClick:this.onClearAll}))}});SetClearButtons=SetClearButtons;var pt=React.PropTypes;var Sortable=React.createClass({displayName:"Sortable",mixins:[PathUpdate],propTypes:{sortableConfig:pt.object,idPrefix:pt.string,className:pt.string,style:pt.object},getDefaultProps:function(){return{sortableConfig:{},idPrefix:"s0rtableThingie"}},intToId:function(i){return this.props.idPrefix+i},idToInt:function(id){return parseInt(id.substring(this.props.idPrefix.length))},handleDrop:function(){var reordering=this.$jq.sortable("toArray").map(this.idToInt);this.$jq.sortable("cancel");var path=this.props.path||[];this.props.update(path,reordering)},componentDidMount:function(){var config=_.clone(this.props.sortableConfig);config.stop=this.handleDrop;this.$jq=$(this.getDOMNode());this.$jq.sortable(config)},render:function(){var wrappedChildren=this.props.children.map(function(child,ix){var id=this.intToId(ix);return React.createElement("div",{id:id,key:id},child)}.bind(this));return React.createElement("div",{className:this.props.className,style:this.props.style},wrappedChildren)}});Sortable=Sortable;var pt=React.PropTypes;var TextArea=React.createClass({displayName:"TextArea",mixins:[PathUpdate,ImmutableUpdate],propTypes:{value:pt.string,name:pt.string,rows:pt.number,cols:pt.number,ref:pt.string,className:pt.string},getInitialState:function(){return{value:this.props.value}},onBlur:function(e){var newValue=e.target.value.trim();if(newValue!==this.props.value){this.props.update(this.props.path,newValue)}},localOnChange:function(e){var newValue=e.target.value;this.setState({value:newValue})},componentWillReceiveProps:function(nextProps){if(this.state.value!==nextProps.value){this.setState({value:nextProps.value})}},render:function(){return React.createElement("textarea",{value:this.state.value,name:this.props.name,rows:this.props.rows,cols:this.props.cols,ref:this.props.ref,className:this.props.className,onBlur:this.onBlur,onChange:this.localOnChange})}});TextArea=TextArea;var pt=React.PropTypes;var ENTER_KEY=13;var TextInput=React.createClass({displayName:"TextInput",mixins:[PathUpdate,ImmutableUpdate],propTypes:{value:pt.string,ref:pt.string,size:pt.number,className:pt.string},getInitialState:function(){return{value:this.props.value}},onBlur:function(e){var newValue=e.target.value.trim();if(newValue!==this.props.value){this.props.update(this.props.path,newValue)}},onKeyPress:function(e){if(e.which===ENTER_KEY){this.onBlur(e)}},localOnChange:function(e){var newValue=e.target.value;this.setState({value:newValue})},componentWillReceiveProps:function(nextProps){if(this.state.value!==nextProps.value){this.setState({value:nextProps.value})}},render:function(){return React.createElement("input",{size:this.props.size,value:this.state.value,ref:this.props.ref,className:this.props.className,onKeyPress:this.onKeyPress,onBlur:this.onBlur,onChange:this.localOnChange})}});TextInput=TextInput;var pt=React.PropTypes;var UserRegions=React.createClass({displayName:"UserRegions",mixins:[PathUpdate,ImmutableUpdate],propTypes:{settings:pt.object},fileInputName:"regionFile",getInitialState:function(){var settings=this.props.settings;var initialRegions=settings?settings.get("regions"):"";return{regions:initialRegions}},setRegions:function(newValue){this.setState({regions:newValue})},getRegions:function(){return this.state.regions},componentWillReceiveProps:function(nextProps){var newRegions=nextProps.settings.get("regions");if(this.state.regions!==newRegions){this.setState({regions:newRegions})}},onChangeFile:function(){this.setRegions("")},resetFileInput:function(){var $fileInput=$('input[type="file"]');$fileInput.wrap("<"+"form"+">").closest("form").get(0).reset();$fileInput.unwrap()},updateTextArea:function(path,newValue){this.setRegions(newValue);this.resetFileInput()},onClear:function(){this.setRegions("");this.resetFileInput()},onCancel:function(){this.props.update(this.props.path.concat("cancel"))},getFileElement:function(){var selector='input[type="file"][name="'+this.fileInputName+'"]';var jqFileInput=$(selector);if(jqFileInput.length!==1){this.error("UserRegions: can't find file input with selector \""+selector+'"')}return jqFileInput},onSubmit:function(){var jqFileInput=this.getFileElement();var fileInputEl=jqFileInput[0];var gotFile=false;if(fileInputEl){if(fileInputEl.files){if(fileInputEl.files.length>0){gotFile=true}}else if(jqFileInput.val()){gotFile=true}}if(gotFile){this.props.update(this.props.path.concat("uploaded"),jqFileInput)}else{this.props.update(this.props.path.concat("pasted"),this.getRegions())}},render:function(){if(this.props.settings&&this.props.settings.get("enabled")){return React.createElement(Modal,{title:"Paste/Upload Regions",path:this.props.path,update:this.props.update},React.createElement("br",null),"Upload file: ",React.createElement("input",{type:"file",name:this.fileInputName,onChange:this.onChangeFile}),React.createElement("br",null),"Or paste regions: ",React.createElement("span",{style:{width:"10em"}}),React.createElement("br",null),React.createElement(TextArea,{value:this.getRegions(),name:"regionText",rows:10,cols:70,path:this.props.path,update:this.updateTextArea}),React.createElement("br",null),React.createElement("input",{type:"button",value:"submit",onClick:this.onSubmit}),React.createElement("input",{type:"button",value:"clear",onClick:this.onClear}),React.createElement("input",{type:"button",value:"cancel",onClick:this.onCancel}),React.createElement("br",null),React.createElement("p",null,"Regions may be either uploaded from a local file or entered"+" "+'in the "Paste regions" input.  Selecting a local file will'+" "+'clear the "Paste regions" input, and entering regions in'+" "+'the "Paste regions" input will clear the file selection.'),React.createElement("p",null,"Regions may be formatted as 3- or 4-field",React.createElement("a",{className:"reactLink",target:"_blank",href:"http://genome.ucsc.edu/FAQ/FAQformat.html#format1"},"BED"),"file format."+" "+"For example:"),React.createElement("pre",null,"#  comment lines can be included starting with the # symbol","\n","chrX   151073054   151173000","\n","chrX   151183000   151190000  optionalRegionName","\n","chrX   151283000   151290000","\n","chrX   151383000   151390000","\n"),React.createElement("p",null,"BED start coordinates are 0-based, i.e. the first base of a"+" "+"chromosome is 0."+" "+"The fourth field, name, is optional and is used only in"+" "+"the Table Browser's correlation function."),React.createElement("p",null,"Regions may also be formatted as coordinate ranges:",React.createElement("pre",null,"chrX:151,283,001-151,290,000  optionalRegionName"),"These are 1-relative coordinates, i.e. the first base of a"+" "+"chromosome is 1."))}else{return null}}});UserRegions=UserRegions;